# Segurança e integridade

## Baixe somente do local oficial

Use apenas os arquivos anexados à página **Releases** deste repositório.

O arquivo de distribuição da release atual é:

`SUPER_LIBRARY_Setup_v1.0.3.exe`

## SHA-256

Cada release publica um arquivo de checksum com o mesmo nome do instalador:

`SUPER_LIBRARY_Setup_v1.0.3.exe.sha256.txt`

No PowerShell:

```powershell
Get-FileHash .\SUPER_LIBRARY_Setup_v1.0.3.exe -Algorithm SHA256
```

O valor deve ser idêntico ao checksum anexado à mesma GitHub Release.

## GitHub Artifact Attestation

A release v1.0.3 usa GitHub Artifact Attestations/Sigstore como camada gratuita de integridade.

Verifique com GitHub CLI:

```powershell
gh attestation verify .\SUPER_LIBRARY_Setup_v1.0.3.exe --repo L3X4RS/super-library-snes9x --predicate-type https://github.com/L3X4RS/super-library-snes9x/attestations/local-release/v1
```

A atestação confirma que os bytes exatos do instalador foram processados e atestados pelo workflow oficial deste repositório. Como a aplicação é compilada localmente a partir de fonte privada, ela não afirma que o GitHub Actions compilou o programa.

Mais detalhes:

`docs/LOCAL_RELEASE_ATTESTATION.md`

## Authenticode / Windows SmartScreen

O projeto pode ser distribuído sem um certificado Authenticode pago. Nesse caso, o Windows ainda pode exibir `Unknown publisher` ou um aviso do SmartScreen para binários novos ou com pouca reputação.

Isso não deve ser confundido com a verificação SHA-256/GitHub Attestation. São mecanismos diferentes.

Quando houver orçamento, um certificado de Code Signing confiável poderá ser adicionado como camada adicional de identidade do publicador.

## Antivírus

SUPER LIBRARY não desativa nem tenta contornar antivírus.

O aplicativo pode, quando solicitado pelo usuário, baixar o Snes9x e shaders de projetos oficiais. Programas novos, pouco difundidos ou sem reputação de assinatura podem eventualmente receber alertas heurísticos.

Se isso ocorrer:

1. não desative a proteção;
2. confirme que o arquivo veio da release oficial;
3. confira o SHA-256;
4. verifique a GitHub Artifact Attestation;
5. mantenha Windows e antivírus atualizados;
6. reporte um possível falso positivo ao fornecedor do antivírus quando apropriado.

## Reportar problema de segurança

Se o repositório estiver com GitHub Security Advisories habilitado, prefira um reporte privado. Não publique dados pessoais, chaves, tokens ou informações sensíveis em issues públicas.
