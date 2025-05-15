# main/resources

## org/dxl/mapper

**MyBatis 的 SQL 映射配置**，定义如何将对象与数据库中的表进行映射和操作

<details><summary>Mapper.xml</summary>

```xml
<?xml version="1.0" encoding="UTF-8" ?><!-- EmpMapper.xml -->
<!DOCTYPE mapper
        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "https://mybatis.org/dtd/mybatis-3-mapper.dtd">

<mapper namespace="org.dxl.mapper.EmpMapper">

    <resultMap id="empResultMap" type="org.dxl.pojo.Emp">
        <!-- 映射 左为数据库中的名字 右为类中的名字 -->
        <result column="username" property="userName"/>
    </resultMap>

    <!-- 登录 -->
    <select id="login" resultMap="empResultMap">
        select * from emp where username = #{userName} and password = #{password}
    </select>

    <!-- 插入 -->
    <insert id="insertEmp">
        insert into emp(username, password)
        values(#{userName}, #{password})
    </insert>

    <!-- 删除 -->
    <delete id="deleteById">
        delete from emp where id = #{id}
    </delete>

    <!-- 批量删除 -->
    <delete id="deleteByIds">
        delete from emp where id in
        <foreach collection="ids" item="id" separator="," open="(" close=")">
            #{id}
        </foreach>
    </delete>

    <!-- 更新 -->
    <update id="updateEmp">
        update emp
        <set>
            <if test="userName != null">
                username=#{userName},
            </if>
            <if test="password != null">
                password=#{password},
            </if>
        </set>
        where id = #{id}
    </update>

    <!-- 查询所有 -->
    <select id="selectEmp" resultMap="empResultMap">
        select * from emp
    </select>

    <!-- 根据id查询 -->
    <select id="selectEmpById" resultMap="empResultMap">
        select * from emp where id = #{id}
    </select>

</mapper>
```

</details>

<br>

---

## application.properties


**项目配置**

<details><summary>application.properties</summary>

```txt
spring.application.name=项目名字

# mysql 配置
spring.datasource.driver-class-name=com.mysql.cj.jdbc.Driver
spring.datasource.url=jdbc:mysql://localhost:3306/数据库名字
spring.datasource.username=root
spring.datasource.password=1234
```
</details>
