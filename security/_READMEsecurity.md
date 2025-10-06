# Security README.md
Team: joao-rib (João Ribeiro), adcampos (Adriana Teixeira)
Folder: security/

## Sprint 1 (22 - 28 Sept 25)
Conteúdo final esperado: Relatório JSON + resumo em Markdown + README.md
Instalar: Trivy + Docker

### Docker Notes
### How to install Docker:
[Docker Installation Guide](https://docs.docker.com/engine/install/)

### Trivy Notes
Trivy is open-source program to scan system vulnerabilities.

It can analise:
- Docker images, code, packages, config files
- Detects known vulnerabilities (based on security databases)
- Will classify how serious the threat is (Critical, high, medium, low)
- It will show details of each threat

### How to install Trivy

- **For Linux Ubuntu or Debian (via apt):**
  - Install dependencies:
    ```bash
    sudo apt update
    sudo apt install -y wget apt-transport-https gnupg lsb-release
    ```
  - Add GPG key to the system:
    ```bash
    wget -qO - https://aquasecurity.github.io/trivy-repo/deb/public.key | sudo gpg --dearmor -o /usr/share/keyrings/trivy.gpg
    ```
  - Add Trivy repository:
    - Try codename-specific (Ubuntu/Debian release):
      ```bash
      echo "deb [signed-by=/usr/share/keyrings/trivy.gpg] https://aquasecurity.github.io/trivy-repo/deb $(lsb_release -sc) main" | sudo tee /etc/apt/sources.list.d/trivy.list
      sudo apt update
      ```
    - If that fails, use generic fallback:
      ```bash
      echo "deb [signed-by=/usr/share/keyrings/trivy.gpg] https://aquasecurity.github.io/trivy-repo/deb generic main" | sudo tee /etc/apt/sources.list.d/trivy.list
      sudo apt update
      ```
  - Install Trivy:
    ```bash
    sudo apt install -y trivy
    ```
  - Verify installation:
    ```bash
    trivy --version
    ```

- **For other operating systems and installation options**, please check the official page:  
[Trivy Installation Guide](https://trivy.dev/latest/getting-started/installation/#__tabbed_1_1)

### How to run the scan.sh script to get results
```bash
./scan.sh <image> --pull
```
Note: flag --pull is optional. It will download the image locally