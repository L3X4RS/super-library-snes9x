# Controles do SUPER LIBRARY

## Gamepad normalizado (SDL)

O SUPER LIBRARY adapta os atalhos de sistema ao tipo de controle conectado para evitar conflito com comandos normais dos jogos.

### Controles modernos com L2/R2

| Função | Xbox | PlayStation | Observação |
|---|---|---|---|
| Anterior / próximo | D-Pad ou analógico esquerdo | D-Pad ou analógico esquerdo | repetição automática ao segurar |
| Play | A | Cross (×) | inicia o jogo selecionado |
| Back | B | Circle (○) | sai do fullscreen ou fecha o launcher em janela |
| Smart Refresh | X | Square (□) | manutenção da biblioteca |
| Snes9x Manager | Y | Triangle (△) | instalar/atualizar/reparar/selecionar emulador |
| Música | LT | L2 | liga/desliga a música do launcher |
| +5 jogos | RB | R1 | no launcher |
| Sair do jogo | RT segurado ~1,2 s | R2 segurado ~1,2 s | durante o Snes9x |
| Configuração | Menu / Start | Options | abre Snes9x sem ROM; pressione novamente para fechar |
| Fechar launcher | View / Back | Share / Create | fechamento direto do frontend |

Durante o gameplay, **R1/RB permanece livre para o jogo**.

### Controles estilo SNES / sem L2 e R2

| Função | Atalho | Observação |
|---|---|---|
| Música | L1 / botão L | liga/desliga a música do launcher |
| Sair do jogo | START + SELECT segurados ~1,2 s | fecha o Snes9x e retorna ao SUPER LIBRARY |

Nos controles sem gatilhos, os botões de ombro normais continuam disponíveis para os jogos.

## Mouse

- metade esquerda/direita do D-Pad: navegação;
- SELECT: menu ROM Library;
- START: configuração do Snes9x;
- A: Play;
- B: Back;
- X: Smart Refresh;
- Y: Snes9x Manager;
- LED: música on/off;
- POWER: fecha o programa.

## Teclado

| Tecla | Ação |
|---|---|
| `Left`, `A`, `W` | Anterior |
| `Right`, `D`, `Down` | Próximo |
| `Enter`, `Return`, `Space`, `S` | Play |
| `R`, `X` | Smart Refresh |
| `F1`, `Y` | Snes9x Manager |
| `Escape`, `Backspace`, `Q` | Back |
| `Page Up` | -5 jogos |
| `Page Down` | +5 jogos |
| `F11` | Fullscreen |

## Controles genéricos

Quando o dispositivo não possui mapeamento SDL normalizado, o programa usa fallback compatível com a disposição mais comum de botões. Em modelos genéricos, a posição física pode variar.

Conectar o controle antes de abrir o SUPER LIBRARY costuma oferecer a experiência mais previsível, embora hot-plug e reconexão também sejam tratados pelo launcher.
