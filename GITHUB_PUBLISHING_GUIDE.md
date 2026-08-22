# Guia de publicação no GitHub

## Versão pública atual

Use **v1.0.3** para a release atual.

- Tag: `v1.0.3`
- Release title: `SUPER LIBRARY v1.0.3`
- Installer: `SUPER_LIBRARY_Setup_v1.0.3.exe`

## Repositório

O repositório público é destinado a documentação e releases binárias. O código-fonte proprietário da aplicação não precisa ser publicado.

Arquivos esperados no repositório:

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
- `CODE_SIGNING.md`
- `docs/`
- `.github/`

## Onde publicar o instalador

Não coloque o instalador no root do repositório.

Use:

**GitHub -> Releases -> Draft a new release -> Attach binaries**

A release deve permanecer como **Draft** durante assinatura, verificação e teste.

## Assinatura digital

A release pública deve usar Authenticode real. O fluxo recomendado está documentado em `CODE_SIGNING.md`.

Para assinatura em nuvem, o projeto usa o workflow:

`.github/workflows/sign-windows-draft-release.yml`

O workflow usa SSL.com eSigner CKA e espera os seguintes GitHub Actions secrets:

- `SSL_ESIGNER_USERNAME`
- `SSL_ESIGNER_PASSWORD`
- `SSL_ESIGNER_TOTP_SECRET`
- `SSL_ESIGNER_MODE`

Para produção, `SSL_ESIGNER_MODE` deve normalmente ser `product`.

## Ordem correta da release

1. Gere a build local a partir da fonte confiável.
2. Faça os testes locais de funcionamento.
3. Assine os binários instalados (`SuperLibrary.exe`, `SNESCore.dll` e `Uninstall SUPER LIBRARY.exe`) quando o ambiente de Code Signing estiver disponível.
4. Gere `SUPER_LIBRARY_Setup_v1.0.3.exe`.
5. Crie uma **Draft Release** com tag `v1.0.3`.
6. Anexe o Setup ainda não publicado ao draft.
7. Execute **Actions -> Sign Windows Draft Release**.
8. Confirme que o workflow terminou com sucesso e que a assinatura Authenticode é válida.
9. Baixe o Setup assinado e faça uma instalação limpa.
10. Só então publique a GitHub Release.

## Checklist funcional antes de publicar

- Launcher abre e fecha normalmente.
- Biblioteca existente é carregada corretamente.
- Refresh funciona com biblioteca grande.
- Importação de ROM funciona.
- Download/associação de capas funciona.
- Download/instalação do Snes9x e shaders funciona.
- Um jogo inicia corretamente.
- Quick Menu funciona com R3 em controles modernos.
- Fallback START+SELECT funciona em controles clássicos sem R3.
- SAVE PROGRESS funciona.
- LOAD PROGRESS funciona.
- Troca de shader funciona.
- RETURN TO LIBRARY funciona sem salvar automaticamente.
- Controles retornam ao Launcher após fechar o emulador.
- Desinstalação funciona.
- Windows Defender e o software de segurança habitual não reportam problema indevido.

## Verificação da assinatura

PowerShell:

```powershell
Get-AuthenticodeSignature .\SUPER_LIBRARY_Setup_v1.0.3.exe | Format-List
```

O resultado esperado para uma release confiável é:

`Status : Valid`

Com SignTool:

```bat
signtool verify /pa /all /v SUPER_LIBRARY_Setup_v1.0.3.exe
```

## SHA-256

Depois da assinatura, gere o hash do arquivo final — nunca do Setup anterior à assinatura:

```powershell
Get-FileHash .\SUPER_LIBRARY_Setup_v1.0.3.exe -Algorithm SHA256
```

Publique o SHA-256 junto com a release e mantenha `SECURITY.md`/release notes sincronizados com o arquivo efetivamente distribuído.
