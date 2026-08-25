# Recursos do SUPER LIBRARY v1.0.3

## Frontend independente para Snes9x

SUPER LIBRARY não substitui o emulador. Ele cria uma camada própria de biblioteca, navegação e sessão, inicia o Snes9x quando necessário e retorna ao frontend quando o emulador fecha.

## Biblioteca visual

- carrossel de capas;
- título do jogo;
- rolagem automática para títulos longos;
- contador de jogos;
- navegação por controle, mouse e teclado;
- Favoritos persistentes;
- até 30 jogos Recentemente Jogados;
- visualizações Todos / Favoritos / Recentes;
- busca instantânea com `Ctrl+F`;
- último jogo jogado separado da simples navegação pela biblioteca.

## Quick Menu em jogo

- R3 abre o Quick Menu em controles modernos;
- START + SELECT abre o mesmo menu em controles clássicos/sem R3;
- R2/RT fica livre durante gameplay;
- o jogo é pausado enquanto o overlay está ativo;
- o input volta ao jogo somente depois que o controle retorna ao estado neutro.

Ações disponíveis:

- RESUME GAME;
- SAVE PROGRESS;
- LOAD PROGRESS;
- VIDEO FILTERS;
- CONTROLLER SETTINGS;
- RETURN TO LIBRARY.

## Save Progress e Continue Playing

- SAVE PROGRESS cria um checkpoint manual por jogo;
- LOAD PROGRESS carrega esse checkpoint;
- CONTINUE PLAYING? é oferecido apenas quando existe um Save Progress explícito;
- sair normalmente do jogo não cria save automático;
- os Save Points ficam separados dos slots normais do Snes9x.

## Video Filters em jogo

- navegação pelos slang-shaders instalados;
- preview durante a sessão quando o build do Snes9x pode ser reconhecido com segurança;
- opção de manter ou cancelar o filtro;
- integração fail-closed: se a estrutura esperada não for validada, o SUPER LIBRARY não tenta modificar o emulador por adivinhação.

## Controller Settings em jogo

Quando a integração pode ser validada com segurança:

- remapeamento do Player 1 dentro do Quick Menu;
- captura pelo caminho WinMM utilizado pelo Snes9x Windows;
- progresso passo a passo por botão/direção;
- cancelamento restaura o mapeamento original.

## Gamepad

- SDL controller mapping;
- bridge isolado da interface Qt;
- USB/Bluetooth;
- hot-plug;
- reconexão depois de fechar o Snes9x;
- diagnóstico de controle com estado do bridge, heartbeat e bateria quando disponível;
- L3 para Favoritos no launcher;
- R3 para alternar a visualização no launcher e abrir o Quick Menu durante gameplay.

## ROM Library

O menu SELECT oferece:

- Choose Folder;
- Import Collection;
- Scan This PC;
- Create Organized Copy;
- Find Missing Covers.

## Import Collection

- trabalha apenas com a coleção fornecida pelo próprio usuário;
- lê pasta, ROM solta, ZIPs e pacotes com múltiplos jogos;
- deduplicação pelo payload real;
- ignora cabeçalho copier comum de 512 bytes na comparação quando aplicável;
- preserva traduções, revisões e regiões que possuem dados realmente diferentes;
- limpa nomes ruidosos apenas na cópia gerenciada;
- origem permanece intacta;
- jogos comuns podem ser regravados como ZIPs validados de uma ROM;
- MSU-1 recebe tratamento específico.

## Estrutura gerenciada de ROMs

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

A migração de layouts anteriores preserva histórico, favoritos e progresso quando os caminhos podem ser reescritos com segurança.

## MSU-1

- reconhece pacotes `.msu1` nativos;
- valida a presença de `program.rom`;
- trata assets de streaming como parte do mesmo jogo lógico;
- evita repacotar desnecessariamente pacotes nativos grandes;
- não converte MSU-1 em um ZIP comum de uma ROM.

## Create Organized Copy

Cria uma nova biblioteca em outro diretório sem modificar a pasta original.

## Smart Refresh

Pode:

- corrigir nomes de capas reconhecidas;
- limpar duplicatas exatas;
- associar ROMs e capas por identidade, aliases, hashes e metadados;
- padronizar ROMs com correspondência de alta confiança;
- converter ROMs soltas reconhecidas em ZIP validado;
- preservar conflitos e correspondências duvidosas em vez de adivinhar;
- respeitar o formato específico de pacotes MSU-1.

## Missing Covers

- LaunchBox Games Database como fonte principal;
- validação de título/plataforma;
- aliases e metadados adicionais;
- fallbacks controlados quando necessário;
- critérios mínimos de dimensão e proporção;
- capas existentes não são substituídas indiscriminadamente.

## Snes9x Manager

- download da release Windows oficial do Snes9x;
- download/instalação de slang-shaders;
- escolha de instalação existente;
- verificação de atualização;
- reparo;
- instalação de shaders ausentes;
- remoção da instalação gerenciada;
- preservação segura de `Snes9x\Roms` antes de manutenção destrutiva;
- registro de origem e hashes do emulador gerenciado.

## Saves

O Snes9x continua responsável por SRAM e seus próprios slots. O SUPER LIBRARY mantém seu progresso adicional dentro de `Snes9x\Saves`, incluindo a árvore de Save Points usada por SAVE PROGRESS.

## Áudio

- música de frontend;
- playlist dinâmica sem quantidade fixa de faixas;
- faixa inicial aleatória;
- crossfade;
- efeitos de interface;
- LED visual de estado;
- preferência persistente;
- música suspensa durante o jogo e restaurada no retorno.

## Distribuição

- Windows 10/11 64-bit;
- Python não é necessário para o usuário final;
- repositório público voltado a documentação e releases binárias;
- SHA-256 e GitHub Artifact Attestation no fluxo de publicação.
