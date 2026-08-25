# Guia de publicação no GitHub

## Versão pública atual

Use **v1.0.3** para a release atual.

- Tag: `v1.0.3`
- Release title: `SUPER LIBRARY v1.0.3`
- Installer esperado: `SUPER_LIBRARY_Setup_v1.0.3.exe`
- Release body template: `GITHUB_RELEASE_BODY_v1.0.3.md`

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
- `GITHUB_RELEASE_BODY_v1.0.3.md`
- `docs/`
- `.github/`

## Onde publicar o instalador

Não coloque o instalador no root do repositório.

Use:

**GitHub → Releases → Draft a new release → Attach binaries**

A release deve permanecer como **Draft** durante verificação e teste.

## Integridade gratuita da release

Enquanto o projeto não possui um certificado Authenticode pago, a release usa:

- SHA-256;
- GitHub Artifact Attestation / Sigstore;
- verificação automática no workflow oficial do repositório;
- teste de instalação limpa antes da publicação.

O workflow é:

`.github/workflows/attest-windows-draft-release.yml`

Ele não exige SSL.com, certificado pago, PFX ou GitHub secrets.

Importante: essa atestação não substitui Authenticode e não remove necessariamente avisos `Unknown publisher`/SmartScreen. Ela comprova a integridade dos bytes e sua vinculação ao workflow oficial do repositório.

## Ordem correta da release v1.0.3

1. Gere a build local a partir da fonte confiável.
2. Faça os testes locais de funcionamento.
3. Gere `SUPER_LIBRARY_Setup_v1.0.3.exe`.
4. Calcule o SHA-256 local do Setup.
5. Abra `GITHUB_RELEASE_BODY_v1.0.3.md` e substitua os dois placeholders pelo nome exato do instalador e pelo SHA-256 final.
6. Crie uma **Draft Release** com tag `v1.0.3` e título `SUPER LIBRARY v1.0.3`.
7. Use o conteúdo final do release body na descrição da Draft Release.
8. Anexe o Setup ao draft.
9. Execute **Actions → Attest Windows Draft Release**.
10. Confirme que o workflow terminou com sucesso.
11. Confirme que a release recebeu:
   - `SUPER_LIBRARY_Setup_v1.0.3.exe.sha256.txt`;
   - `SUPER_LIBRARY_Setup_v1.0.3.exe.VERIFY.txt`.
12. Baixe novamente o Setup da Draft Release.
13. Faça uma instalação limpa e execute o checklist funcional abaixo.
14. Só então publique a GitHub Release.

## Checklist funcional antes de publicar

- Launcher abre e fecha normalmente.
- Biblioteca existente é carregada corretamente.
- Refresh funciona com biblioteca grande.
- Importação de ROM funciona.
- Estrutura `Snes9x\Roms` permanece correta.
- Importação PT-BR / região funciona.
- Pacote MSU-1 testado, se houver um disponível.
- Download/associação de capas funciona.
- Download/instalação do Snes9x e shaders funciona.
- Um jogo inicia corretamente.
- Quick Menu funciona com R3 em controles modernos.
- Fallback START+SELECT funciona em controles clássicos sem R3.
- R2/RT permanece livre durante gameplay.
- SAVE PROGRESS funciona.
- LOAD PROGRESS funciona.
- CONTINUE PLAYING? aparece somente depois de SAVE PROGRESS.
- RETURN TO LIBRARY não salva automaticamente.
- VIDEO FILTERS funciona no build de Snes9x testado.
- CONTROLLER SETTINGS funciona no build/controlador testado quando a integração é suportada.
- Controles retornam ao Launcher após fechar o emulador.
- Favoritos / Recentes / busca funcionam.
- Desinstalação funciona.
- Windows Defender e o software de segurança habitual não reportam problema indevido.

## Verificar SHA-256

PowerShell:

```powershell
Get-FileHash .\SUPER_LIBRARY_Setup_v1.0.3.exe -Algorithm SHA256
```

Compare com o `.sha256.txt` anexado à mesma release.

## Verificar GitHub Artifact Attestation

Com GitHub CLI:

```powershell
gh attestation verify .\SUPER_LIBRARY_Setup_v1.0.3.exe --repo L3X4RS/super-library-snes9x --predicate-type https://github.com/L3X4RS/super-library-snes9x/attestations/local-release/v1
```

A semântica dessa atestação está documentada em:

`docs/LOCAL_RELEASE_ATTESTATION.md`

## Authenticode no futuro

Quando houver orçamento para um certificado Code Signing confiável, Authenticode pode ser adicionado ao fluxo sem remover SHA-256 nem GitHub Artifact Attestations.

Até lá, não anuncie a release como `digitally signed by SUPER LIBRARY`. Windows pode continuar exibindo `Unknown publisher`, o que é esperado para uma release sem certificado Authenticode confiável.
