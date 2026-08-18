# Segurança e integridade

## Baixe somente do local oficial
Use apenas os arquivos anexados à página **Releases** deste repositório.

O arquivo de distribuição recomendado é:

`SUPER_LIBRARY_Setup_v1.0.0.exe`

## SHA-256
Cada release deve publicar o SHA-256 do instalador. Antes de divulgar a versão, o mantenedor deve substituir o campo abaixo pelo hash real do arquivo final:

`SHA-256: <PREENCHER APÓS COMPILAR/ASSINAR O SETUP FINAL>`

No PowerShell:

```powershell
Get-FileHash .\SUPER_LIBRARY_Setup_v1.0.0.exe -Algorithm SHA256
```

## Antivírus
SUPER LIBRARY não desativa nem tenta contornar antivírus.

O aplicativo pode, quando solicitado pelo usuário, baixar o Snes9x e shaders de projetos oficiais. Programas novos, pouco difundidos ou ainda sem reputação de assinatura podem eventualmente receber alertas heurísticos de produtos de segurança.

Se isso ocorrer:

1. não desative a proteção;
2. confirme que o arquivo veio da release oficial;
3. confira o SHA-256;
4. mantenha Windows e antivírus atualizados;
5. reporte um possível falso positivo ao fornecedor do antivírus quando apropriado.

Para distribuição pública, assinatura **Authenticode/Code Signing** do executável e do instalador é fortemente recomendada.

## Reportar problema de segurança
Se o repositório estiver com GitHub Security Advisories habilitado, prefira um reporte privado. Não publique dados pessoais, chaves, tokens ou informações sensíveis em issues públicas.
