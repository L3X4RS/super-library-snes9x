# Controles do SUPER LIBRARY v1.0.3

## Gamepad normalizado (SDL)

O SUPER LIBRARY usa uma camada SDL isolada da interface principal para navegação, hot-plug e reconexão USB/Bluetooth.

Os atalhos de sistema mudam de contexto entre o launcher e o gameplay para evitar conflito com os jogos.

## No launcher

### Controles modernos

| Função | Xbox / XInput | PlayStation | Observação |
|---|---|---|---|
| Anterior / próximo | D-Pad ou analógico esquerdo | D-Pad ou analógico esquerdo | navegação da biblioteca |
| Play | A | Cross (×) | inicia o jogo selecionado |
| Back | B | Circle (○) | volta / sai do fullscreen / fecha quando aplicável |
| Smart Refresh | X | Square (□) | manutenção da biblioteca |
| Snes9x Manager | Y | Triangle (△) | instalar/atualizar/reparar/selecionar emulador |
| Música | LT | L2 | liga/desliga a música do launcher |
| Página anterior | LB | L1 | volta 5 jogos |
| Próxima página | RB | R1 | avança 5 jogos |
| Favorito | L3 | L3 | adiciona/remove o jogo atual dos Favoritos |
| Visualização | R3 | R3 | Todos → Favoritos → Recentemente Jogados |
| Configuração | Menu / Start | Options | abre Snes9x sem ROM |
| Fechar launcher | View / Back | Share / Create | fecha o SUPER LIBRARY |

## Durante gameplay

### Controles modernos com R3

**R3 abre o Quick Menu.**

R2/RT não é usado pelo SUPER LIBRARY durante gameplay e permanece disponível para o jogo.

No Quick Menu:

- D-Pad / analógico: navegação;
- A / Cross: confirmar;
- B / Circle: voltar / retomar quando aplicável;
- R3: fechar o Quick Menu e retornar ao jogo.

Ações do Quick Menu:

- RESUME GAME;
- SAVE PROGRESS;
- LOAD PROGRESS;
- VIDEO FILTERS;
- CONTROLLER SETTINGS;
- RETURN TO LIBRARY.

O jogo fica pausado enquanto o overlay está ativo. Antes de devolver o controle ao jogo, o SUPER LIBRARY aguarda o input ficar neutro para evitar que o botão usado no menu vire um comando dentro da emulação.

### Controles estilo SNES / sem R3

Use **START + SELECT juntos** para abrir o mesmo Quick Menu.

Esse fallback existe para controles 8/16-bit que não possuem clique nos analógicos.

R2/RT não participa desse fluxo e os ombros normais permanecem disponíveis aos jogos.

## Controller Settings dentro do jogo

Quando o build do Snes9x pode ser reconhecido e validado com segurança, **CONTROLLER SETTINGS** permite remapear o Player 1 sem sair da sessão.

O assistente pede cada direção/botão em sequência e captura pelo caminho de joystick WinMM usado pelo port Windows do Snes9x.

Se a integração não puder ser validada, nenhuma configuração é alterada por adivinhação.

## Video Filters dentro do jogo

No menu **VIDEO FILTERS**:

- D-Pad / analógico: navega pelos shaders;
- seleção destaca o filtro para preview quando suportado;
- A / Cross: mantém/confirma;
- B / Circle: volta;
- R3: fecha o overlay e retorna ao jogo.

## Mouse

No launcher:

- metade esquerda/direita do D-Pad: navegação;
- SELECT: menu ROM Library;
- START: configuração do Snes9x;
- A: Play;
- B: Back;
- X: Smart Refresh;
- Y: Snes9x Manager;
- LED: música on/off;
- POWER: fecha o programa.

Os overlays em jogo também aceitam mouse/teclado, mas o fluxo principal é projetado para funcionar por controle.

## Teclado

| Tecla | Ação |
|---|---|
| `Left`, `A`, `W` | jogo anterior |
| `Right`, `D`, `Down` | próximo jogo |
| `Enter`, `Return`, `Space`, `S` | Play |
| `R`, `X` | Smart Refresh |
| `F1`, `Y` | Snes9x Manager |
| `F2` | adicionar/remover Favorito |
| `F3` | Todos → Favoritos → Recentemente Jogados |
| `F4` | diagnóstico do controle |
| `Ctrl+F` | busca instantânea |
| `Escape`, `Backspace`, `Q` | Back |
| `Page Up` | -5 jogos |
| `Page Down` | +5 jogos |
| `F11` | Fullscreen |

## Diagnóstico do controle

`F4` abre informações úteis de suporte, como estado do bridge, tempo desde o heartbeat e bateria quando o driver/SDL fornece essa informação.

## Controles genéricos

Quando o dispositivo não possui mapeamento SDL normalizado, a compatibilidade pode depender do fallback do joystick e do modo exposto pelo driver.

Se o controle oferece XInput, normalmente esse é o modo mais previsível no Windows. Hot-plug e reconexão são tratados pelo launcher, mas modelos genéricos podem apresentar ordem física diferente de botões.
