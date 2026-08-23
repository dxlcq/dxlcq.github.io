## 参考


<br>

---

## INSTALL

```bash
sudo docker run --rm -d --name minio \
  -p 9000:9000 -p 9001:9001 \
  -e MINIO_ROOT_USER=root \
  -e MINIO_ROOT_PASSWORD=password \
  quay.io/minio/minio server /data --console-address ":9001"
```