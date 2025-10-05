from fastapi import FastAPI

app = FastAPI()

@app.get("/health")
def health_check():
    return {"status": "ok"}

@app.get("/info")
def info():
    return {"project": "Security Dashboard", "version": "1.0"}
