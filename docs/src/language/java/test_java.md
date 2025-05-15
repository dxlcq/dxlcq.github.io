# test/java

## org/dxl

<details><summary>ApplicationTests.java</summary>

```java
// EmpApplicationTests.java
package org.dxl;

import jakarta.annotation.Resource;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;
import org.dxl.mapper.EmpMapper;
import org.dxl.pojo.Emp;

import java.util.List;

@SpringBootTest
class SpringbootWebMybatisCrudApplicationTests {

    @Resource
    EmpMapper empMapper;

    @Test
    void testInsertEmp(){
        Emp emp = new Emp();
        emp.setUserName("root");
        emp.setPassword("1234");
        empMapper.insertEmp(emp);
    }

    @Test
    void testDeleteById(){
        empMapper.deleteById(2);
    }

    @Test
    void testDeleteByIds(){
        empMapper.deleteByIds(List.of(3, 4));
    }

    @Test
    void testUpdateEmp(){
        Emp emp = new Emp();
        emp.setId(1);
        emp.setUserName("root");
        emp.setPassword("1234");
        empMapper.updateEmp(emp);
    }

    @Test
    void testSelectEmp(){
        List<Emp> list = empMapper.selectEmp();
        for (Emp e : list){
            System.out.println(e);
        }
    }

    @Test
    void testSelectEmpById(){
        Emp emp = empMapper.selectEmpById(1);
        System.out.println(emp);
    }
}
```
</details>

