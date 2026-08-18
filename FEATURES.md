# Recursos do SUPER LIBRARY

## Frontend independente para Snes9x
SUPER LIBRARY não substitui o emulador. Ele cria uma camada de biblioteca e navegação própria, lança o Snes9x quando necessário e retorna ao frontend quando o emulador fecha.

## Biblioteca visual
- carrossel de capas;
- título do jogo;
- rolagem automática para títulos longos;
- contador de jogos;
- navegação por controle, mouse e teclado.

## ROM Library
O menu SELECT oferece:
- Choose Folder;
- Import Collection;
- Scan This PC;
- Create Organized Copy;
- Find Missing Covers.

## Import Collection
- trabalha com coleção fornecida pelo próprio usuário;
- leitura de pasta, ROM solta e ZIPs;
- deduplicação pelo payload real;
- ignora cabeçalho copier comum de 512 bytes na comparação;
- preserva traduções, revisões e regiões que realmente possuem dados diferentes;
- perfis PT-BR, Auto/Mixed, USA, Europe e Japan;
- origem mantida como somente leitura durante a importação.

## Create Organized Copy
Cria uma nova biblioteca em ZIPs validados sem modificar a pasta original.

## Smart Refresh
Pode corrigir capas reconhecidas, limpar duplicatas, padronizar ROMs com correspondência de alta confiança e criar ZIPs validados. Correspondências duvidosas são preservadas.

## Missing Covers
Busca capas faltantes usando metadados/índices e pesquisa online, com validação visual e critérios de qualidade. Capas existentes são preservadas e downloads podem manter backup do original.

## Snes9x Manager
- download do Snes9x oficial;
- download de slang-shaders;
- escolha de instalação existente;
- verificação de atualização;
- reparo;
- instalação de shaders ausentes;
- remoção da instalação gerenciada.

## Gamepad
- SDL controller mapping;
- USB/Bluetooth;
- hot-plug;
- reconexão após fechar o Snes9x;
- R1/RB segurado para voltar do jogo.

## Áudio
- música de frontend;
- efeitos de interface;
- LED visual de estado;
- preferência de música persistente;
- música suspensa durante o jogo e restaurada no retorno.
