<div align="center">

# SUPER LIBRARY
### An independent SNES library interface for Snes9x

**Uma experiência de biblioteca para Super Nintendo no Windows, com navegação por controle, organização da coleção, Quick Menu em jogo, Save Progress, filtros de vídeo e integração com Snes9x.**

![Windows](https://img.shields.io/badge/Windows-10%20%7C%2011-0078D4?logo=windows&logoColor=white)
![Release](https://img.shields.io/badge/release-v1.0.3-6f42c1)
![Frontend](https://img.shields.io/badge/frontend-Snes9x-b55bd6)
![ROMs](https://img.shields.io/badge/ROMs-not%20included-important)

</div>

![SUPER LIBRARY interface](docs/images/super-library-interface.png)

---

## O que é o SUPER LIBRARY?

O **SUPER LIBRARY** é uma interface independente para **Snes9x** criada para transformar uma coleção local de jogos de Super Nintendo em uma experiência de navegação mais próxima de um console.

Ele não substitui o emulador. O SUPER LIBRARY organiza a biblioteca, gerencia capas e coleções, inicia o Snes9x, acompanha a sessão de jogo e oferece recursos próprios antes, durante e depois da emulação.

A versão **v1.0.3** consolida a linha atual do projeto com:

- Quick Menu em jogo;
- Save Progress e Load Progress;
- prompt **CONTINUE PLAYING?** somente quando o usuário criou um save manual;
- preview e aplicação de filtros/shaders durante o jogo;
- configuração do controle Player 1 dentro do Quick Menu quando o build do Snes9x pode ser validado com segurança;
- Favoritos, Recentemente Jogados e busca instantânea;
- diagnóstico de controle;
- biblioteca gerenciada em `Snes9x\Roms`;
- organização física de ROMs Standard, PT-BR e MSU-1;
- instalação/atualização gerenciada do Snes9x oficial e slang-shaders;
- proteção adicional para ROMs, saves e manutenção da instalação.

> **Importante:** o SUPER LIBRARY **não inclui ROMs comerciais, não oferece catálogo de ROMs e não baixa jogos comerciais**. Use somente arquivos obtidos e mantidos de acordo com as leis aplicáveis na sua região.

---

## Download

Baixe sempre a versão mais recente pela página **Releases** deste repositório.

Para a v1.0.3, use o **instalador completo** anexado à release. Não copie apenas o `SuperLibrary.exe` de uma instalação existente.

### Requisitos

- Windows 10 ou Windows 11 64-bit;
- resolução recomendada de 1280×720 ou superior;
- controle USB ou Bluetooth opcional, reconhecido pelo Windows/SDL;
- internet apenas para funções online, como instalar/atualizar Snes9x, shaders e procurar capas;
- Python não é necessário no computador do usuário.

---

## Veja o SUPER LIBRARY em ação

### Favoritos

<p align="center">
  <img src="docs/images/Aba%20de%20Favoritos.png" alt="SUPER LIBRARY - Favoritos" width="100%">
</p>

Jogos favoritos ficam salvos entre sessões e podem ser exibidos em uma visualização própria da biblioteca.

### Save Progress

<p align="center">
  <img src="docs/images/Salvar%20a%20qualqer%20momento.png" alt="SUPER LIBRARY - Salvar progresso" width="100%">
</p>

Durante o jogo, o Quick Menu permite criar um ponto manual com **SAVE PROGRESS**. Esse ponto fica separado dos slots normais do Snes9x.

### Continue Playing

<p align="center">
  <img src="docs/images/Continuar%20de%20onde%20parou.png" alt="SUPER LIBRARY - Continuar jogo" width="100%">
</p>

Na próxima abertura daquele jogo, o SUPER LIBRARY exibe **CONTINUE PLAYING?** somente quando existe um Save Progress criado explicitamente pelo jogador. Sair do jogo sem salvar não cria um resume automático escondido.

---

## Primeira configuração

1. Instale e abra o **SUPER LIBRARY**.
2. Use **SELECT** e escolha **Choose Folder** para apontar para sua biblioteca existente, ou **Import Collection** para criar uma cópia gerenciada e organizada.
3. Use **Y — SNES9X** e escolha **Download Snes9x and Shaders**.
4. Se já possui Snes9x, escolha **Choose Existing**.
5. Navegue pelos jogos e pressione **A / Cross** ou clique em **A — PLAY**.

Quando o Snes9x fecha, o SUPER LIBRARY volta automaticamente e restaura o fluxo da biblioteca.

---

## Quick Menu durante o jogo

A v1.0.3 usa um Quick Menu próprio durante a emulação.

### Controles modernos

Pressione **R3** durante o jogo.

- R3 abre/fecha o Quick Menu;
- **R2 / RT fica totalmente livre para o jogo**;
- o jogo é pausado enquanto o menu está ativo;
- antes de devolver o input ao jogo, o SUPER LIBRARY aguarda o controle voltar ao estado neutro.

### Controles clássicos sem R3

Controles 8/16-bit ou sem clique nos analógicos usam **START + SELECT** juntos para abrir o mesmo Quick Menu.

### Ações disponíveis

- **RESUME GAME** — fecha o Quick Menu e continua o jogo;
- **SAVE PROGRESS** — salva o momento atual para continuar depois;
- **LOAD PROGRESS** — carrega o Save Progress existente daquele jogo;
- **VIDEO FILTERS** — navega e faz preview de filtros/shaders sem sair do jogo;
- **CONTROLLER SETTINGS** — remapeia o Player 1 enquanto o jogo está pausado, quando a integração com o build do Snes9x pode ser validada com segurança;
- **RETURN TO LIBRARY** — fecha o Snes9x e retorna à biblioteca.

**RETURN TO LIBRARY não salva automaticamente.** Um ponto de continuação só existe quando o usuário escolhe **SAVE PROGRESS**.

---

## Video Filters em jogo

O SUPER LIBRARY integra os slang-shaders instalados no Snes9x e oferece navegação em jogo por uma interface própria.

Quando o build do Snes9x é reconhecido e validado pelo bridge:

- filtros podem ser pré-visualizados durante a sessão;
- o shader pode ser mantido ou cancelado;
- o jogo não precisa ser fechado apenas para navegar pelos filtros;
- se a estrutura esperada do Snes9x não puder ser validada, a integração falha de forma segura e não tenta adivinhar endereços de memória.

A seleção continua sendo uma configuração do Snes9x; o SUPER LIBRARY apenas fornece a experiência de navegação e aplicação.

---

## Controles no launcher

O frontend usa uma camada SDL isolada para USB/Bluetooth, hot-plug e reconexão.

| Ação | Xbox / XInput | PlayStation | Função |
|---|---|---|---|
| Navegar | D-Pad / analógico esquerdo | D-Pad / analógico esquerdo | jogo anterior / próximo |
| Jogar | A | Cross (×) | abre o jogo selecionado |
| Voltar | B | Circle (○) | volta / sai do fullscreen / fecha quando aplicável |
| Smart Refresh | X | Square (□) | manutenção da biblioteca |
| Snes9x Manager | Y | Triangle (△) | instalar, atualizar, reparar ou selecionar Snes9x |
| Música | LT | L2 | liga/desliga a música do launcher |
| Página anterior | LB | L1 | volta 5 jogos |
| Próxima página | RB | R1 | avança 5 jogos |
| Favorito | L3 | L3 | adiciona/remove o jogo dos Favoritos |
| Visualização | R3 | R3 | Todos → Favoritos → Recentemente Jogados |
| Configurar emulador | Menu / Start | Options | abre Snes9x sem ROM |
| Fechar launcher | View / Back | Share / Create | fecha o SUPER LIBRARY |

Durante gameplay, **R3 pertence ao Quick Menu** e **R2/RT permanece livre para o jogo**.

### Teclado

| Tecla | Ação |
|---|---|
| `←`, `A` ou `W` | jogo anterior |
| `→`, `D` ou `↓` | próximo jogo |
| `Enter`, `Return`, `Space` ou `S` | jogar |
| `R` ou `X` | Smart Refresh |
| `F1` ou `Y` | Snes9x Manager |
| `F2` | adicionar/remover Favorito |
| `F3` | Todos → Favoritos → Recentemente Jogados |
| `F4` | diagnóstico do controle |
| `Ctrl+F` | busca instantânea |
| `Esc`, `Backspace` ou `Q` | voltar / fechar |
| `Page Up` | volta 5 jogos |
| `Page Down` | avança 5 jogos |
| `F11` | alterna fullscreen |

Veja [CONTROLS.md](CONTROLS.md) para a referência completa.

---

## Biblioteca de ROMs

O menu **SELECT — ROM Library** concentra as operações de biblioteca.

### Choose Folder

Aponta diretamente para uma pasta existente de ROMs compatíveis.

### Import Collection

Importa a coleção fornecida pelo próprio usuário e cria uma biblioteca gerenciada sem modificar a origem.

O importador:

- aceita pasta, ROM solta, ZIP e pacotes com múltiplos jogos;
- identifica o payload real da ROM;
- remove/ignora apenas duplicatas exatas;
- preserva revisões, regiões e traduções realmente diferentes;
- limpa nomes ruidosos na cópia gerenciada;
- converte jogos comuns em ZIPs validados de uma ROM;
- reconhece e preserva o fluxo específico de MSU-1;
- mantém a coleção de origem intacta.

A estrutura final da biblioteca gerenciada é:

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

### MSU-1

Pacotes `.msu1` nativos são tratados como um jogo lógico com `program.rom` e assets de streaming. O SUPER LIBRARY evita repacotar desnecessariamente pacotes nativos grandes e não transforma MSU-1 em um ZIP comum.

### Scan This PC

Procura uma pasta compatível no computador e pede confirmação antes de adotá-la.

### Create Organized Copy

Cria uma nova cópia organizada em outro diretório sem alterar a coleção original.

### Find Missing Covers

Procura artes ausentes usando metadados e fontes online. O LaunchBox Games Database é a fonte principal, com fallbacks controlados quando não há correspondência adequada.

---

## Smart Refresh

O **X — REFRESH** executa manutenção da biblioteca com critérios conservadores de confiança.

Ele pode:

- restaurar nomes de capas reconhecidas por identidade de imagem;
- remover duplicatas exatas reconhecidas;
- associar ROMs e capas por título, aliases, hashes e metadados;
- padronizar ROMs reconhecidas;
- converter ROMs soltas reconhecidas em ZIP validado;
- preservar conflitos e correspondências duvidosas em vez de adivinhar;
- tratar pacotes MSU-1 sem repacotar seu conteúdo como uma ROM comum.

> O Smart Refresh pode alterar arquivos da biblioteca gerenciada quando a correspondência é considerada segura. Para uma operação totalmente não destrutiva sobre a coleção original, use **Create Organized Copy**.

---

## Favoritos, Recentes e busca

A v1.0.3 mantém estado persistente da biblioteca:

- **Favoritos** por jogo;
- até **30 jogos recentemente jogados**;
- filtro entre Todos, Favoritos e Recentes;
- busca instantânea com `Ctrl+F`;
- último jogo efetivamente jogado separado da simples navegação pela biblioteca.

---

## Snes9x Manager

O botão **Y — SNES9X** concentra o gerenciamento do emulador.

O SUPER LIBRARY pode:

- baixar a release Windows mais recente do repositório oficial do Snes9x;
- instalar slang-shaders do projeto libretro;
- usar um Snes9x já existente;
- verificar atualizações;
- reparar a instalação gerenciada;
- reinstalar shaders ausentes;
- remover a instalação gerenciada.

Durante reparos/remoções, a biblioteca de ROMs é preservada em uma localização segura antes de qualquer operação destrutiva sobre os arquivos do emulador.

O projeto também grava informações de procedência e hashes do Snes9x gerenciado para auxiliar em verificações de integridade e possíveis falsos positivos de antivírus.

---

## Saves e progresso

O Snes9x continua responsável por SRAM e seus save states normais. O SUPER LIBRARY mantém seus próprios pontos de progresso dentro da árvore de saves gerenciada:

```text
Snes9x\Saves\
├── Quick Resume\
└── Save Points\
```

Na v1.0.3, o fluxo visível ao usuário é baseado em **SAVE PROGRESS**. O prompt **CONTINUE PLAYING?** não é criado por uma saída normal do jogo.

---

## Música e interface

- playlist interna dinâmica;
- todos os `.ogg` incluídos na biblioteca interna entram automaticamente na reprodução;
- faixa inicial aleatória;
- crossfade entre faixas;
- música suspensa durante gameplay e retomada ao voltar ao launcher;
- efeitos sonoros de interface;
- LED visual de música;
- preferência persistente.

---

## Estrutura e distribuição

A instalação pública é projetada para manter a árvore principal limpa. O runtime Python/PySide não é exposto como uma pasta permanente comum ao lado do launcher.

A distribuição pública do GitHub é um **repositório de documentação e releases binárias**. O código-fonte proprietário do SUPER LIBRARY não é publicado por esta licença.

Veja:

- [QUICK_START.md](QUICK_START.md)
- [CONTROLS.md](CONTROLS.md)
- [FEATURES.md](FEATURES.md)
- [FAQ.md](FAQ.md)
- [SECURITY.md](SECURITY.md)
- [CODE_SIGNING.md](CODE_SIGNING.md)
- [GITHUB_PUBLISHING_GUIDE.md](GITHUB_PUBLISHING_GUIDE.md)

---

## Segurança e integridade

Baixe o instalador somente pela página oficial **Releases** deste repositório.

A publicação da v1.0.3 usa:

- SHA-256 do instalador;
- GitHub Artifact Attestation / Sigstore no workflow oficial;
- teste de instalação antes da publicação.

Isso **não é Authenticode**. Enquanto o projeto não usar um certificado Code Signing confiável, o Windows ainda pode mostrar `Unknown publisher` ou avisos de SmartScreen para binários novos.

O SUPER LIBRARY não desativa e não tenta contornar antivírus. Veja [SECURITY.md](SECURITY.md).

---

## Projeto independente

SUPER LIBRARY é um projeto independente e não é afiliado, endossado ou publicado pela Nintendo, Snes9x, libretro, LaunchBox ou outros detentores de marcas e projetos citados.

Nintendo, Super Nintendo, SNES e marcas relacionadas pertencem aos respectivos titulares. Snes9x e demais componentes de terceiros mantêm suas próprias licenças e direitos.

Veja [NOTICE.md](NOTICE.md) e [LICENSE.md](LICENSE.md).
