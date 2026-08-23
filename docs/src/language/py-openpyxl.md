[官网文档](https://openpyxl.readthedocs.io/en/stable/tutorial.html)

## 工作薄

* 打开工作薄

```py
wb = openpyxl.load_workbook('wb.xlsx')
```

* 新建工作薄

```py
wb = openpyxl.Workbook()
```

* 保存工作薄（保存之前的操作）

```py
wb.save('wb.xlsx')
```

## 工作表

* 打开表
```py
Sheet1 = wb['Sheet1']
```

* 新建表

```py
one = wb.create_sheet('one', 0) # 插入到最前面
two = wb.create_sheet('two')    # 插入到最后面
```

* 删除表

```py
wb.remove(sheet1)
```

* 查看所有表

```py
print(wb.sheetnames)
```

* 更改表名

```py
Sheet1.title = 'Sheet2'
```

## 行 row

* 最大行

```py
print(Sheet1.max_row)
```

## 列 column

* 最大列

```py
print(Sheet1.max_column)
```

## 单元格 cell

* 获取单元格的值

```py
print(Sheet1['A1'].value)
print(Sheet1.cell(row = 1, column = 1).value)
```

* 设置单元格的值

```py
Sheet1['A1'] = 'world'
Sheet1.cell(row = 1, column = 1).value = 'world'
```