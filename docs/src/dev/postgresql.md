## 参考

* [PostgreSQL Docker hub](https://hub.docker.com/_/postgres)

## 启动

```bash
sudo docker run -e POSTGRES_PASSWORD=postgres -d -p 5432:5432 postgres
```

```bash
sudo apt install postgresql-client
psql -h localhost -U postgres -d postgres
```

## 查

* 查看所有数据库

```sql
\l
```

## 增

## 删

## 改
