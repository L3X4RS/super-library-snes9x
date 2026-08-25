# FAQ — SUPER LIBRARY v1.0.3

## Preciso instalar Python?

**Não.** A distribuição final leva o runtime necessário. O usuário não precisa instalar Python, PySide6, pygame ou pip.

## O programa inclui ROMs?

**Não.** SUPER LIBRARY não distribui, oferece catálogo nem fornece download de ROMs comerciais.

## O programa inclui Snes9x dentro do instalador?

O frontend pode instalar o Snes9x oficial sob demanda quando o usuário escolhe **Download Snes9x and Shaders**. Também é possível selecionar uma instalação existente.

## Preciso de internet para jogar?

Não, depois que sua biblioteca e o Snes9x estão configurados. Internet é usada para recursos como instalação/atualização do emulador, shaders e busca de capas.

## Posso usar meu próprio Snes9x?

Sim. Use **Y — SNES9X → Choose Existing**.

## Como configuro vídeo e áudio do Snes9x?

No launcher, use **START / Options / Menu** para abrir o Snes9x sem ROM e acessar suas configurações nativas.

## Como volto ao SUPER LIBRARY durante um jogo?

Na v1.0.3, o retorno passa pelo **Quick Menu**:

- controle moderno: pressione **R3**;
- controle clássico/sem R3: pressione **START + SELECT juntos**.

Escolha **RETURN TO LIBRARY**.

## O R2/RT continua livre nos jogos?

**Sim.** R2/RT não é interceptado pelo SUPER LIBRARY durante gameplay.

## O Quick Menu salva automaticamente quando eu saio?

**Não.** RETURN TO LIBRARY apenas encerra o Snes9x e volta à biblioteca.

Um ponto de continuação só é criado quando você escolhe **SAVE PROGRESS**.

## Quando aparece CONTINUE PLAYING?

Somente quando existe um checkpoint criado explicitamente por **SAVE PROGRESS** para aquele jogo.

O diálogo oferece:

- Continue;
- Start Normally;
- Cancel.

Iniciar normalmente não apaga o Save Progress existente.

## Posso carregar meu progresso durante o jogo?

Sim. Abra o Quick Menu e use **LOAD PROGRESS**. A opção fica indisponível quando ainda não existe Save Progress para aquele jogo.

## Posso trocar shader sem sair do jogo?

Sim, quando o build do Snes9x em uso pode ser reconhecido e validado com segurança pela integração da v1.0.3.

Abra **Quick Menu → VIDEO FILTERS**. O SUPER LIBRARY pode oferecer preview e aplicação durante a sessão.

Se a estrutura esperada do Snes9x não puder ser validada, o sistema falha de forma segura e não tenta modificar o processo por adivinhação.

## Posso configurar o controle durante o jogo?

Quando a integração compatível pode ser validada, use **Quick Menu → CONTROLLER SETTINGS**.

O assistente remapeia o **Player 1** passo a passo pelo caminho de joystick usado pelo Snes9x Windows. Cancelar restaura a configuração anterior.

## Posso usar DualSense / DualShock?

O frontend usa SDL para sua própria navegação. DualShock 4 e DualSense normalmente são reconhecidos no Windows/SDL por USB ou Bluetooth, embora o comportamento exato dependa do driver e do modo de conexão.

## Posso usar controle Xbox?

Sim. Controles XInput são um dos cenários mais diretos de compatibilidade no Windows.

## E controles 8BitDo / estilo SNES?

Podem funcionar quando reconhecidos pelo Windows/SDL. Controles sem R3 usam **START + SELECT** para abrir o Quick Menu durante gameplay.

## E controles genéricos?

Podem funcionar por mapeamento SDL ou fallback de joystick. A ordem física dos botões pode variar dependendo do dispositivo/driver. Quando houver opção de XInput, esse modo costuma ser o mais previsível.

## O launcher reconhece conexão/desconexão do controle?

Sim. O bridge trata hot-plug e reconexão. O trabalho SDL roda isolado da interface Qt para reduzir risco de travamento da GUI por driver/dispositivo.

## Como vejo diagnóstico do controle?

Pressione **F4** no launcher. A tela pode mostrar estado do bridge, tempo desde o heartbeat e bateria quando o driver/SDL realmente fornece essa informação.

## Como funcionam Favoritos e Recentemente Jogados?

- `F2` ou L3 alterna Favorito no jogo selecionado;
- `F3` ou R3 alterna entre Todos, Favoritos e Recentemente Jogados no launcher;
- a lista de Recentes mantém até 30 jogos efetivamente abertos.

Durante gameplay, R3 muda de contexto e abre o Quick Menu.

## Como faço busca rápida?

Use `Ctrl+F` e digite parte do nome do jogo.

## O que o Smart Refresh altera?

Ele pode alterar arquivos da biblioteca quando uma correspondência é considerada segura: corrigir nomes de capas, remover duplicatas reconhecidas, padronizar ROMs e converter ROMs soltas em ZIP validado.

Casos duvidosos e conflitos são preservados em vez de adivinhados.

## Quero organizar sem alterar minha pasta original.

Use **SELECT → Create Organized Copy** ou **Import Collection** para trabalhar em uma cópia gerenciada. A coleção de origem não é modificada pelo importador.

## Como a biblioteca gerenciada é organizada?

```text
Snes9x\Roms\
├── Standard\
│   ├── USA\
│   ├── Europe\
│   ├── Japan\
│   └── Other\
├── Translations\
│   └── PT-BR\
└── MSU-1\
```

## O importador remove traduções ou revisões diferentes?

Não por nome. A deduplicação usa o payload real. Se duas ROMs têm conteúdo diferente, traduções, regiões e revisões podem coexistir.

## Como o SUPER LIBRARY trata MSU-1?

MSU-1 recebe tratamento próprio. Pacotes `.msu1` nativos são validados como um jogo lógico com `program.rom` e assets de streaming e não são convertidos em um ZIP comum de uma ROM.

## Como funciona a busca de capas?

O SUPER LIBRARY prioriza o **LaunchBox Games Database** para correspondências confiáveis e usa fontes auxiliares apenas quando necessário. Título, aliases, plataforma, dimensões e outros sinais são usados para reduzir falsos positivos.

## A música aceita várias faixas?

Sim. A playlist é dinâmica: os arquivos `.ogg` incluídos na biblioteca interna entram automaticamente na reprodução. A faixa inicial é escolhida aleatoriamente e há crossfade entre músicas.

## O que acontece ao reparar/remover o Snes9x gerenciado?

A árvore de ROMs é preservada antes de operações destrutivas sobre os arquivos do emulador. Se a preservação segura não puder ser feita, a operação deve falhar em vez de colocar a biblioteca em risco.

## Meu antivírus alertou sobre o programa. O que faço?

Não desative a proteção.

1. confirme que o instalador veio da página oficial Releases;
2. confira o SHA-256 publicado;
3. verifique a GitHub Artifact Attestation quando disponível;
4. mantenha o software de segurança atualizado;
5. use o processo de falso positivo do fornecedor quando apropriado.

Veja [SECURITY.md](SECURITY.md).

## O GitHub contém o código-fonte do aplicativo?

Não. Este repositório é destinado a **documentação e releases binárias**. A licença pública não concede uma licença open-source ao código-fonte proprietário do SUPER LIBRARY.

## Onde encontro mais documentação?

- [README.md](README.md)
- [QUICK_START.md](QUICK_START.md)
- [CONTROLS.md](CONTROLS.md)
- [FEATURES.md](FEATURES.md)
- [SECURITY.md](SECURITY.md)
