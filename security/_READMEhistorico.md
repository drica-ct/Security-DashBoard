# Security-DashBoard

<img width="476" height="309" alt="image" src="https://github.com/user-attachments/assets/1aa9c5a2-01bb-4bb4-a315-a58e9a6d5c5d" />

# Semana 1 – Setup e Primeiros Passos

Começa: **22 Setembro**    
Prazo final: **29 Setembro**

- Cada equipa tem liberdade para escolher as ferramentas que preferir, desde que cumpram as tarefas propostas.
- Se quiserem ir além do que está listado, estão à vontade; posso disponibilizar as tarefas das próximas semanas caso queiram avançar mais rápido.
- É necessário que se organizem internamente para dividir e coordenar as tarefas entre os membros da equipa.
- Em caso de dúvidas ou dificuldades, contactem-me sem hesitar.

---

## Equipa 1 – Infraestrutura e DevOps
**Membros:** husamuel, edfreder  
**Pasta de trabalho:** `devops/`  
**Conteúdo final esperado:** Dockerfile + docker-compose.yml + README.md  
**Instalar:** Docker  

### Tarefas:
- Criar a pasta `devops/` no repositório.  
- Criar um `Dockerfile` simples que levante um servidor básico.  
- Criar um ficheiro `docker-compose.yml` para orquestrar o container.  
- Escrever um guia (`README.md`) com instruções de como correr o container.  
- Testar localmente o build e o run do container.  
- Fazer commit e push para o GitHub.  

---

## Equipa 2 – Backend e Integração de Dados
**Membros:** mreinald, tfilipe  
**Pasta de trabalho:** `backend/`  
**Conteúdo final esperado:** API com duas rotas + README.md  
**Instalar:** Python 3.9+, pip  

### Tarefas:
- Criar a pasta `backend/` no repositório.  
- Criar o ficheiro `requirements.txt` (FastAPI + Uvicorn).  
- Criar `main.py` com uma rota simples `/health`.  
- Acrescentar uma segunda rota `/info` que devolve uma mensagem estática (ex: nome do projeto e versão).  
- Escrever um `README.md` com instruções para correr a API.  
- Testar se a API responde localmente.  
- Fazer commit e push para o GitHub.  

---

## Equipa 3 – Frontend e Experiência do Utilizador
**Membros:** ddo-carm, aaugusto  
**Pasta de trabalho:** `frontend/`  
**Conteúdo final esperado:** Projeto React/Tailwind + componente de HealthCheck + README.md  
**Instalar:** Node.js LTS + npm  

### Tarefas:
- Criar a pasta `frontend/` no repositório.  
- Inicializar o projeto com React + Vite.  
- Instalar e configurar TailwindCSS.  
- Criar uma página inicial simples com o título do projeto e um layout base (menu ou cabeçalho).  
- Adicionar um componente `HealthCheck` que simula uma chamada à rota `/health` do backend e mostra “Backend Online” ou “Offline”.  
- Escrever um `README.md` com instruções para correr o projeto.  
- Fazer commit e push para o GitHub.  

---

## Equipa 4 – Segurança e Monitoramento
**Membros:** joao-rib, adcampos 
**Pasta de trabalho:** `security/`  
**Conteúdo final esperado:** Relatório JSON + resumo em Markdown + README.md  
**Instalar:** Trivy + Docker  

### Tarefas:
- Criar a pasta `security/` no repositório.  
- Usar o Trivy para analisar uma imagem Docker (ex: Nginx).  
- Exportar os resultados em JSON e guardar no repositório.  
- Criar um relatório em Markdown (`report.md`) com resumo dos problemas encontrados (ex: número de vulnerabilidades críticas, médias, baixas).  
- Escrever um `README.md` explicando o que é o Trivy, como instalar e como correr a análise.  
- Fazer commit e push para o GitHub.  

--------------------------------------------------------------
--------------------------------------------------------------
--------------------------------------------------------------

# Security-DashBoard

<img width="1920" height="979" alt="image" src="https://github.com/user-attachments/assets/d1944501-f240-421b-92c5-552bb4391f2f" />

- Imagem de referência para Frontend

- [Backlog](https://github.com/husamuel/Security-DashBoard/blob/main/Backlog.md)

#  Semana 2 – Desenvolvimento do MVP Integrado

Começa: **29 Setembro**    
Prazo final: **12 Outubro**

- Cada equipa tem liberdade para escolher as ferramentas que preferir, desde que cumpram as tarefas propostas.
- Se quiserem ir além do que está listado, estão à vontade; posso disponibilizar as tarefas das próximas semanas caso queiram avançar mais rápido.
- É necessário que se organizem internamente para dividir e coordenar as tarefas entre os membros da equipa.
- Em caso de dúvidas ou dificuldades, contactem-me sem hesitar.


## Objetivo final do sprint
Ter um protótipo navegável em que:
- O **backend** expõe mais endpoints e já processa o primeiro relatório do Trivy.
- O **frontend** mostra informação real (não apenas “Online/Offline”).
- O **DevOps** consegue orquestrar pelo menos 3 containers (frontend, backend, db).
- O **Security** gera relatórios e já fornece resumo para o backend consumir.

---

## 🔹 Equipa 1 – Infraestrutura e DevOps (2 membros)

### Meta
Orquestração mínima com 3 serviços.

### Tarefas Semana 2
- **Dockerfiles**:
  - Criar Dockerfile otimizado para backend (com FastAPI + Uvicorn).
  - Criar Dockerfile otimizado para frontend (build React → servido em Nginx).
- **docker-compose.yml**:
  - Adicionar 3 containers:
    - backend (FastAPI).
    - frontend (React+Nginx).
    - db (Postgres ou Mongo, mesmo que vazio no início).
  - Criar volume `db_data` para persistência da base de dados.
  - Criar rede interna (`security-dashboard-net`) para comunicação.
- Testar o build + run → validar que o frontend consegue chamar o backend via `http://backend:8000`.
- Atualizar `README.md` com instruções de orquestração.

### 📌 Entrega Semana 2
`docker-compose up` levanta frontend, backend e DB.

---

## 🔹 Equipa 2 – Backend e Integração de Dados (2 membros)

### Meta
Backend expõe endpoints para começar a alimentar o dashboard.

### Tarefas Semana 2
- Expandir API com mais 3 endpoints:
  - `/vulnerabilities` → lê `security/report.json` e devolve resumo (crit/alto/médio/baixo).
  - `/security-report` → devolve relatório JSON completo.
  - `/metrics` → devolver dados simulados (CPU, memória, uptime).
- Integrar DB container (mesmo que por enquanto só criar tabela/coleção de logs vazia).
- Criar estrutura do projeto: separar `routes/`, `services/`, `models/`.
- Escrever testes simples para validar os 3 novos endpoints.
- Atualizar documentação (Swagger já embutido no FastAPI).
- Atualizar `README.md`.

### 📌 Entrega Semana 2
Backend já expõe `/health`, `/info`, `/vulnerabilities`, `/security-report` e `/metrics`.

---

## 🔹 Equipa 3 – Frontend e UX (3 membros)

### Meta
Criar primeiras páginas funcionais que mostram dados reais do backend.

### Tarefas Semana 2
- **Layout base**:
  - Criar sidebar/menu de navegação.
  - Criar cabeçalho com título do projeto.
- **Página Inicial (Home)**:
  - Mostrar `/health` (backend online/offline).
  - Mostrar `/info` (nome do projeto + versão).
- **Página Vulnerabilidades**:
  - Criar componente `VulnerabilitiesSummary` (mostra crit/alto/médio/baixo).
  - Consumir API `/vulnerabilities`.
- **Página Métricas**:
  - Criar `MetricsDashboard` com dados de `/metrics` (mesmo que ainda simulados).
- **Divisão de tarefas entre 3 devs**:
  - Dev1 → Layout base + Home.
  - Dev2 → Vulnerabilidades.
  - Dev3 → Métricas.
- Atualizar `README.md` com instruções + screenshot da UI.

### 📌 Entrega Semana 2
Dashboard já tem Home, Vulnerabilidades e Métricas (dados reais/simulados).

---

## 🔹 Equipa 4 – Segurança e Monitoramento (2 membros)

### Meta
Gerar relatórios JSON para alimentar o backend.

### Tarefas Semana 2
- Criar script `scan.sh` que roda Trivy em pelo menos 2 imagens (ex: `nginx:latest` e `python:3.9`).
- Exportar resultados para `report.json` dentro de `security/`.
- Criar `report.md` com resumo automático:
  - Nº vulnerabilidades críticas, altas, médias, baixas.
- Testar integração → garantir que o backend consegue ler `report.json`.
- Documentar no `README.md` (como correr scan e gerar relatórios).

### 📌 Entrega Semana 2
Relatório JSON atualizado + resumo em Markdown.

---

##  Resultado final da Semana 2
- **DevOps**: `docker-compose up` já sobe frontend, backend e db.
- **Backend**: expõe endpoints `/health`, `/info`, `/vulnerabilities`, `/security-report`, `/metrics`.
- **Frontend**: tem Home, Vulnerabilidades e Métricas, mostrando dados reais.
- **Segurança**: fornece `report.json` que backend já consome.
