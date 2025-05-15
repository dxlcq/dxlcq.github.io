## id 选择器

```html
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8"> 
        <title> 网页名称 </title>

        <style>
            #one
            {
                color:red;
            }

            #two
            {
                color:green;
            }
        </style>

    </head>

    <body>
        <p id="one"> 网页内容 </p>
        <p id="two"> 网页内容 </p>
    </body>
</html>
```

## class 选择器

```html
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8"> 
        <title> 网页名称 </title>

        <style>
            .one{
                color:red;
            }

            p.two{
                color:green;
            }

            .center{
                text-align:center;
            }
        </style>
    </head>
    <body>
        <p> 网页内容 </p>
        <p class = "one"> 网页内容 </p>
        <p class = "two center"> 网页内容 </p>
    </body>
</html>
```

## 盒子模型

```html
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8"> 
        <title> 网页名称 </title>

        <style>
            div{
                background-color: lightgrey;/* 背景颜色 */
                
                margin: 100px;                /* 边框外面一层 */
                border: 50px solid green;   /* 边框大小 */
                padding: 100px ;              /* 边框里面一层 */
                
                text-align:center;
            }
        </style>
    </head>
    <body>
        <div>网页内容</div>
    </body>
</html>
```