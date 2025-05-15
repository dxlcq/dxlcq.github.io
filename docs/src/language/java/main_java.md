# main/java

## org/dxl/utils

<details><summary>JwtUtils.java</summary>

```java
// JwtUtils.java
package org.dxl.utils;

import io.jsonwebtoken.Claims;
import io.jsonwebtoken.Jws;
import io.jsonwebtoken.JwsHeader;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.security.Keys;
import io.jsonwebtoken.security.SecureDigestAlgorithm;

import javax.crypto.SecretKey;
import java.time.Instant;
import java.util.Date;
import java.util.Map;
import java.util.UUID;

public class JwtUtils {
    private static final String SECRET = "12345678901234567890123456789012"; // 32个字节的密钥
    private static final Integer expireTime = 12 * 60 * 60; // token有效期
    private static final String ISSUER = "dxl"; // Token 签发者
    private static final SecureDigestAlgorithm<SecretKey, SecretKey> ALGORITHM = Jwts.SIG.HS256; // 签名算法

    //subject: token 使用主体，通常是token所有人的ID
    // username 和 userid 用于 payload
    public static String buildJwt(String subject, Map<String, Object> claims){
        String uuid = UUID.randomUUID().toString();
        Date expireDate = Date.from(Instant.now().plusSeconds(expireTime));
        //HMAC : Hash-based Message Authentication Code
        SecretKey KEY = Keys.hmacShaKeyFor(SECRET.getBytes()); // 基于密钥产生 SecretKey
        return Jwts.builder()
                .header()
                //设置头部信息header
                .add("typ", "JWT")
                .add("alg", "HS256")
                .and()
                //设置自定义负载信息payload
                .claims(claims)
                //令牌ID
                .id(uuid)
                // 过期时间
                .expiration(expireDate)
                //生效时间
                .notBefore(new Date())
                //签发时间
                .issuedAt(new Date())
                //令牌所有者，通常是用户ID
                .subject(subject)
                //签发者
                .issuer(ISSUER)
                //签名
                .signWith(KEY, ALGORITHM)
                .compact();
    }

    public static Jws<Claims> parseToken(String token) {
        SecretKey KEY = Keys.hmacShaKeyFor(SECRET.getBytes());
        return Jwts.parser()
                .verifyWith(KEY)
                .build()
                .parseSignedClaims(token);
    }

    public static JwsHeader parseHeader(String token) {
        return parseToken(token).getHeader();
    }

    public static Claims parsePayload(String token) {
        return parseToken(token).getPayload();
    }

    public static String getSubject(String token) {
        return parseToken(token).getPayload().getSubject();
    }

    public static boolean validateToken(String token) {
        try {
            parseToken(token);
            return true;
        } catch (Exception e) {
            return false;
        }
    }
}

/*
<dependency>
    <groupId>io.jsonwebtoken</groupId>
    <artifactId>jjwt</artifactId>
    <version>0.12.5</version>
</dependency>
*/
```
</details>

## org/dxl/interceptor

<details><summary>LoginCheckInterceptor.java</summary>

```java
// LoginCheckInterceptor.java
package org.dxl.interceptor;

import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Component;
import org.springframework.util.StringUtils;
import org.springframework.web.servlet.HandlerInterceptor;
import org.springframework.web.servlet.ModelAndView;
import org.dxl.utils.JwtUtils;

@Slf4j
@Component
public class LoginCheckInterceptor implements HandlerInterceptor {
    @Override
    // 目标资源方法运行前执行，返回 true: 执行；返回 false: 不执行
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        //1. 获取请求头中的令牌
        String jwt = request.getHeader("token");
        //2. 判断令牌是否存在
        if (!StringUtils.hasLength(jwt)){
            log.info("请求头token为空，返回未登录的信息");
            return false;
        }
        //3. 解析token,如果解析失败，返回 false
        try{
            JwtUtils.parseToken(jwt);
        }catch (Exception e){ // 解析失败
            log.info("token解析失败");
            return false;
        }
        //解析token成功
        return HandlerInterceptor.super.preHandle(request, response, handler);
    }

    @Override
    // 目标资源方法运行后执行
    public void postHandle(HttpServletRequest request, HttpServletResponse response, Object handler, ModelAndView modelAndView) throws Exception {
        HandlerInterceptor.super.postHandle(request, response, handler, modelAndView);
    }

    @Override
    // 视图渲染完毕后执行，最后运行，执行释放资源的工作
    public void afterCompletion(HttpServletRequest request, HttpServletResponse response, Object handler, Exception ex) throws Exception {
        HandlerInterceptor.super.afterCompletion(request, response, handler, ex);
    }
}
```
</details>

## org/dxl/config

<details><summary>WebConfig.java</summary>

```java
// WebConfig.java
package org.dxl.config;

import jakarta.annotation.Resource;
import org.springframework.context.annotation.Configuration;

import org.springframework.web.servlet.config.annotation.InterceptorRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;
import org.dxl.interceptor.LoginCheckInterceptor;

@Configuration
public class WebConfig implements WebMvcConfigurer {
    @Resource
    private LoginCheckInterceptor loginCheckInterceptor;

    @Override
    public void addInterceptors(InterceptorRegistry registry) {
        registry.addInterceptor(loginCheckInterceptor).addPathPatterns("/**").excludePathPatterns("/login");
        WebMvcConfigurer.super.addInterceptors(registry);
    }
}
```
</details>

## org/dxl/pojo

**普通 Java 对象**，常用于封装数据传输对象

* `@Override` 重写父类方法

* `Lombok` 提供的注解：
    * `@Data` 用于自动生成类的 `toString()` 等
    * `@NoArgsConstructor` 自动生成无参构造方法
    * `@AllArgsConstructor`自动生成包含所有成员变量的构造方法

<details><summary>Result.java</summary>

```java
package org.dxl.pojo;

/**
 * 统一响应结果封装类
 */
public class Result {
    private Integer code ;//1 成功 , 0 失败
    private String msg; //提示信息
    private Object data; //数据 date

    public Result() {
    }
    public Result(Integer code, String msg, Object data) {
        this.code = code;
        this.msg = msg;
        this.data = data;
    }
    public Integer getCode() {
        return code;
    }
    public void setCode(Integer code) {
        this.code = code;
    }
    public String getMsg() {
        return msg;
    }
    public void setMsg(String msg) {
        this.msg = msg;
    }
    public Object getData() {
        return data;
    }
    public void setData(Object data) {
        this.data = data;
    }

    public static Result success(Object data){
        return new Result(1, "success", data);
    }
    public static Result success(){
        return new Result(1, "success", null);
    }
    public static Result error(String msg){
        return new Result(0, msg, null);
    }

    @Override
    public String toString() {
        return "Result{" +
                "code=" + code +
                ", msg='" + msg + '\'' +
                ", data=" + data +
                '}';
    }
}
```
</details>

<details><summary>PageBean.java</summary>

```java
package org.dxl.pojo;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.List;

/**
 * 分页查询结果封装类
 */
@Data
@NoArgsConstructor
@AllArgsConstructor
public class PageBean {
    private Long total;     // 总记录数
    private List<Emp> rows; // 当前页数据列表
}
```
</details>

<details><summary>Emp.java</summary>

```java
package org.dxl.pojo;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * 普通用户类
 */
@Data
@NoArgsConstructor
@AllArgsConstructor
public class Emp {
    private Integer id;                 // 员工编号
    private String userName;            // 用户名
    private String password;            // 密码
    private String name;                // 姓名
    private Short gender;               // 性别
    private String image;               // 头像
    private Short job;                  // 职务
    private LocalDate entryDate;        // 入职日期
    private Integer deptId;             // 部门编号
    private LocalDateTime createTime;   // 创建时间
    private LocalDateTime updateTime;   // 更新时间
}
```
</details>

<details><summary>Dept.java</summary>

```java
package org.dxl.pojo;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import java.time.LocalDateTime;

/**
 * 普通部门类
 */
@Data
@NoArgsConstructor
@AllArgsConstructor
public class Dept {
    private Integer id;                 // ID
    private String name;                // 部门名称
    private LocalDateTime createTime;   // 创建时间
    private LocalDateTime updateTime;   // 修改时间
}
```
</details>


<br>

---


## org/dxl/mapper

**映射器**，`MyBatis` 等组件使用

* `@Mapper` 使用 `MyBatis` 框架为接口生成对应实现类

<details><summary>Mapper</summary>

```java
// EmpMapper.java
package org.dxl.mapper;

import org.apache.ibatis.annotations.Mapper;
import org.dxl.pojo.Emp;

import java.util.List;

@Mapper
public interface EmpMapper {
    // 增
    void insertEmp(Emp emp);            // insert into emp values(...);
    // 删
    void deleteById(int id);            // delete from emp where id = ?;
    void deleteByIds(List<Integer> ids);// delete from emp where id in (...);
    // 改
    void updateEmp(Emp emp);            // update emp set ... where id = ?;
    // 查
    List<Emp> selectEmp();              // select * from emp;
         Emp  selectEmpById(int id);    // select * from emp where id = ?;
    // 登录
    Emp login(Emp emp);                 // select * from emp where username = ? and password = ?;
}
```
</details>


<br>

---


## org/dxl/service

**服务层**，封装业务逻辑和数据处理，提供给 `Controller` 使用

调用 `DAO` 层实现对数据的访问和操作

* `@Server` 标识为 `Spring Bean`，由 `Spring` 管理的服务类
* `@Resource` 依赖注入

<details><summary>Service</summary>

```java
// EmpService.java
package org.dxl.service;

import org.dxl.pojo.Emp;
import java.util.List;

public interface EmpService {
    // 增
    void insertEmp(Emp emp);
    // 删
    void deleteById(int id);
    void deleteByIds(List<Integer> ids);
    // 改
    void updateEmp(Emp emp);
    // 查
    List<Emp> selectEmp();
         Emp  selectEmpById(int id);
    // 登录
    Demo login(Demo demo);
}
```
</details>

<details><summary>impl/ServiceImpl</summary>

```java
// EmpServiceImpl.java
package org.dxl.service.impl;

import jakarta.annotation.Resource;
import org.dxl.mapper.EmpMapper;
import org.dxl.pojo.Emp;
import org.dxl.service.EmpService;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class EmpServiceImpl implements EmpService {
    @Resource
    EmpMapper empMapper;

    @Override
    public void insertEmp(Emp emp) {
        empMapper.insertEmp(emp);
    }

    @Override
    public void deleteById(int id) {
        empMapper.deleteById(id);
    }

    @Override
    public void deleteByIds(List<Integer> ids) {
        empMapper.deleteByIds(ids);
    }

    @Override
    public void updateEmp(Emp emp) {
        empMapper.updateEmp(emp);
    }

    @Override
    public List<Emp> selectEmp() {
        return empMapper.selectEmp();
    }

    @Override
    public Emp selectEmpById(int id) {
        return empMapper.selectEmpById(id);
    }

    @Override
    public Demo login(Demo demo) {
        return demoMapper.login(demo);
    }
}

```
</details>


<br>

---


## org/dxl/controller

**控制器**，处理 `HTTP` 请求，返回 `HTTP` 响应，调用业务逻辑返回结果

* `@RestController` 处理 HTTP 请求并返回响应数据
* `@Resource` 依赖注入，解耦一个类对其依赖对象的创建和管理过程
* `@GetMapping` 处理 HTTP GET 请求
* `@PostMapping` 处理 HTTP POST 请求
* `@PutMapping` 处理 HTTP PUT 请求
* `@RequestParam` 从请求中获取 key 的 value，并且赋值给某个变量
* `@PathVariable` 用于从 URL 路径中提取变量
* `@RequestBody` 将 HTTP 请求体中的内容绑定到方法参数上

<details><summary>Controller</summary>

```java
// EmpController.java
package org.dxl.controller;

import jakarta.annotation.Resource;
import org.dxl.pojo.Emp;
import org.dxl.pojo.Result;
import org.dxl.service.EmpService;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
public class EmpController {
    @Resource
    EmpService empService;              // 暂时按照自动实例化、智能指针理解吧

    @PostMapping("/insert")             // 处理客户端对 "/insert" 路径的 POST 请求
    public Result insertEmp(@RequestBody Emp emp) {
        empService.insertEmp(emp);      // 调用服务层
        return Result.success();        // 返回一个 Result
    }

    @DeleteMapping("/delete/{id}")      // 处理客户端对 "/delete/{id}" 路径的 DELETE 请求
    public Result deleteById(@PathVariable Integer id) {
        empService.deleteById(id);
        return Result.success();
    }

    @DeleteMapping("/delete")           // 处理客户端对 "/delete" 路径的 DELETE 请求
    public Result deleteByIds(@RequestBody List<Integer> ids) {
        empService.deleteByIds(ids);
        return Result.success();
    }

    @PutMapping("/update")              // 处理客户端对 "/update" 路径的 PUT 请求
    public Result updateEmp(@RequestBody Emp emp) {
        empService.updateEmp(emp);
        return Result.success();
    }

    @GetMapping("/select")              // 处理客户端对 "/list" 路径的 GET 请求
    public Result selectEmp() {
        List<Emp> e = empService.selectEmp();
        return Result.success(e);
    }

    @GetMapping("/select/{id}")         // 处理客户端对 "/select/{id}" 路径的 Get 请求
    public Result selectEmpById(@PathVariable Integer id) {
        Emp e = empService.selectEmpById(id);
        return Result.success(e);
    }
}
```
</details>


<details><summary>LoginController.java</summary>

```java
// LoginController.java
package org.dxl.controller;

import jakarta.annotation.Resource;
import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;
import org.dxl.pojo.Emp;
import org.dxl.pojo.Result;
import org.dxl.service.EmpService;
import org.dxl.utils.JwtUtils;

import java.util.HashMap;
import java.util.Map;

@Slf4j
@RestController
public class LoginController {
    @Resource
    EmpService empService;

    @PostMapping("/login")
    public Result login(@RequestBody Emp emp){
        Emp e = empService.login(emp);
        // 登录成功，生成令牌，下发令牌
        if (e != null){
            Map<String, Object> map = new HashMap<>();
            map.put("username", e.getUserName());
            map.put("id", e.getId());
            String jwt = JwtUtils.buildJwt(e.getId().toString(), map);
            return Result.success(jwt);
        }
        else{
            // 登陆失败，返回错误信息
            return Result.error("用户名或密码错误");
        }
    }
}
```
</details>