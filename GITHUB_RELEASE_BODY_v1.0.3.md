# SUPER LIBRARY v1.0.3 🎮

A versão **1.0.3** consolida a experiência atual do SUPER LIBRARY para **Snes9x**, com biblioteca visual, Quick Menu em jogo, progresso manual, filtros de vídeo e organização avançada da coleção.

## Destaques

- **Quick Menu em jogo** pelo R3;
- fallback **START + SELECT** para controles clássicos sem R3;
- **R2/RT permanece livre para os jogos**;
- **SAVE PROGRESS** e **LOAD PROGRESS**;
- **CONTINUE PLAYING?** somente quando o usuário criou um Save Progress manual;
- **VIDEO FILTERS** com preview/aplicação durante a sessão quando o build do Snes9x pode ser validado com segurança;
- **CONTROLLER SETTINGS** para Player 1 dentro do Quick Menu em builds compatíveis;
- Favoritos, Recentemente Jogados e busca instantânea;
- diagnóstico de controle;
- USB/Bluetooth, hot-plug e reconexão;
- biblioteca gerenciada em `Snes9x\Roms`;
- organização Standard / PT-BR / MSU-1;
- importação da coleção do próprio usuário com deduplicação pelo payload real;
- instalação/atualização gerenciada do Snes9x oficial e slang-shaders;
- Smart Refresh e busca de capas;
- música dinâmica com crossfade;
- Python não é necessário para o usuário final.

## Primeiros passos

1. Baixe o **Setup v1.0.3** anexado abaixo.
2. Instale e abra o SUPER LIBRARY.
3. Use **SELECT → Choose Folder** ou **Import Collection**.
4. Use **Y → Download Snes9x and Shaders** ou selecione um Snes9x existente.
5. Escolha um jogo e pressione **A / Cross**.

## Quick Menu

Durante gameplay:

- **R3** em controles modernos;
- **START + SELECT** em controles clássicos/sem R3.

O Quick Menu oferece:

- RESUME GAME;
- SAVE PROGRESS;
- LOAD PROGRESS;
- VIDEO FILTERS;
- CONTROLLER SETTINGS;
- RETURN TO LIBRARY.

**RETURN TO LIBRARY não cria save automático.**

## Biblioteca gerenciada

```text
Snes9x\Roms\
├── Standard\USA
├── Standard\Europe
├── Standard\Japan
├── Standard\Other
├── Translations\PT-BR
└── MSU-1
```

SUPER LIBRARY não inclui, oferece ou baixa ROMs comerciais.

## Integridade

**Installer:** `<PREENCHER COM O NOME EXATO DO SETUP FINAL>`

**SHA-256:** `<PREENCHER COM O SHA-256 DO SETUP FINAL>`

Depois do upload da Draft Release, execute o workflow **Attest Windows Draft Release** e confirme os arquivos de verificação antes de publicar.

> GitHub Artifact Attestation/Sigstore comprova integridade/proveniência do arquivo processado pelo workflow, mas não substitui Authenticode. Builds sem certificado Code Signing podem continuar exibindo `Unknown publisher`/SmartScreen.

Documentação completa:

- [README.md](README.md)
- [QUICK_START.md](QUICK_START.md)
- [CONTROLS.md](CONTROLS.md)
- [FEATURES.md](FEATURES.md)
- [SECURITY.md](SECURITY.md)
