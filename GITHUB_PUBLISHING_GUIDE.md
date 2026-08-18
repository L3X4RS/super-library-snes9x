# Guia de publicação no GitHub

## Versionamento recomendado
Use **v1.0.0**.

Para uma primeira versão pública estável, `1.0.0` é mais claro e profissional do que começar em `1.0.5`. As revisões anteriores podem permanecer como histórico interno de desenvolvimento.

- Tag: `v1.0.0`
- Release title: `SUPER LIBRARY 1.0 — First Public Stable Release`
- Installer: `SUPER_LIBRARY_Setup_v1.0.0.exe`

## Nome do repositório
Sugestões:

- `super-library-snes9x`
- `super-library`

## Description / About

**PT-BR**
> Interface independente para Snes9x com biblioteca visual de SNES, suporte a gamepad, gerenciamento de ROMs, capas e shaders.

**EN**
> Independent Windows frontend for Snes9x with a console-like SNES library, gamepad support, ROM management, covers and shaders.

## Topics

`super-nintendo` · `snes` · `snes9x` · `frontend` · `launcher` · `retrogaming` · `emulation` · `windows` · `gamepad` · `rom-library`

## O que colocar no repositório

Suba os arquivos deste pacote de documentação:

- `README.md`
- `README.en.md`
- `QUICK_START.md`
- `CONTROLS.md`
- `FEATURES.md`
- `FAQ.md`
- `SECURITY.md`
- `NOTICE.md`
- `LICENSE.md`
- `CHANGELOG.md`
- `docs/`
- `.github/`

**Não precisa publicar a estrutura do projeto nem o código-fonte.**

## Onde colocar o EXE

Não coloque o instalador como um arquivo normal no root do repositório.

Use:

**GitHub → Releases → Draft a new release → Attach binaries**

Anexe apenas:

`SUPER_LIBRARY_Setup_v1.0.0.exe`

Cole o conteúdo de `GITHUB_RELEASE_BODY_v1.0.0.md` como descrição da release.

## Antes de publicar

1. Compile a build pública v1.0.0.
2. Assine os binários/Setup com Code Signing se possuir certificado.
3. Faça uma instalação limpa.
4. Confirme o ícone do EXE e atalhos.
5. Teste abrir/fechar o launcher.
6. Teste escolher uma biblioteca.
7. Teste **Download Snes9x and Shaders** até o fim.
8. Teste iniciar um jogo.
9. Teste segurar R1/RB para voltar.
10. Teste retorno do controle e da música.
11. Teste START/Options para configuração do Snes9x.
12. Teste desinstalação.
13. Faça uma verificação com o antivírus do Windows e seu software de segurança habitual.
14. Gere o SHA-256 do instalador final.
15. Substitua o placeholder de SHA em `SECURITY.md` e no corpo da release.

PowerShell:

```powershell
Get-FileHash .\SUPER_LIBRARY_Setup_v1.0.0.exe -Algorithm SHA256
```
