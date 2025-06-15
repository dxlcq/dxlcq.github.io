## 参考


<br>

---

## 一键启动

```bash
sudo docker run --rm -d --gpus all -p 11434:11434 -v /home/jiao/.ollama:/root/.ollama ollama/ollama
```

<br>

---

## REST API

```bash
curl http://localhost:11434/api/generate -d '{
  "model": "qwen3:4b",
  "prompt":"你是gg还是mm"
}'
```