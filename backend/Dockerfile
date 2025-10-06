FROM python:3.9
WORKDIR /backend 
COPY . backend.py 
RUN pip install --no-cache-dir flask
CMD ["python", "backend.py"]
EXPOSE 5001

# --no-cache-dir serve para não guardar ficheiros temporários