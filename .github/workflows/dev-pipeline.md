# Pipeline Dev

**Disparado em:** push ou pull request para a branch `dev`.

## 1. Buscar o código
- Fazer checkout da branch `dev` para ter o código mais recente.

## 2. Instalar dependências
- Separar instalação para **front-end** e **back-end**.
- Garantir que todas as dependências necessárias para testes e build estejam disponíveis.

## 3. Executar verificações de qualidade (Lint)
- Lint para **front-end**.
- Lint para **back-end**.
- Lint para scripts e configuração.

## 4. Executar testes
- **Unitários**: testar funções isoladas do front e back.
- **Integração**: testar integração entre front-end e back-end.
- **Security tests**: verificar vulnerabilidades, dependências inseguras, configurações incorretas.

## 5. Construir o projeto
- Build do **front-end**.
- Build do **back-end**.
- Criar **containers Docker** para front-end, back-end e security.

## 6. Deploy para ambiente dev (opcional)
- Fazer deploy dos containers ou aplicações front/back/security no ambiente dev.
