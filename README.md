<div align="center">

# SUPER LIBRARY
### An independent SNES library interface for Snes9x

**Uma experiência de biblioteca para Super Nintendo no Windows, com navegação por controle, organização automática, Quick Resume e integração com Snes9x.**

![Windows](https://img.shields.io/badge/Windows-10%20%7C%2011-0078D4?logo=windows&logoColor=white)
![Release](https://img.shields.io/badge/release-v1.0.1-6f42c1)
![Frontend](https://img.shields.io/badge/frontend-Snes9x-b55bd6)
![ROMs](https://img.shields.io/badge/ROMs-not%20included-important)

</div>

![SUPER LIBRARY interface](docs/images/super-library-interface.png)

---

## Veja o SUPER LIBRARY em ação

### ⭐ Favoritos

<p align="center">
  <img src="docs/images/Aba%20de%20Favoritos.png" alt="SUPER LIBRARY - Favoritos" width="100%">
</p>

Marque seus jogos preferidos e acesse uma visualização dedicada da biblioteca. O estado de Favorito permanece salvo entre sessões.

### 💾 Salve seu progresso ao sair

<p align="center">
  <img src="docs/images/Salvar%20a%20qualqer%20momento.png" alt="SUPER LIBRARY - Salvar progresso" width="100%">
</p>

Ao retornar ao SUPER LIBRARY durante um jogo, você pode criar um ponto de continuação antes de fechar o Snes9x — sem precisar lidar manualmente com slots ou arquivos de save state.

### ▶️ Continue exatamente de onde parou

<p align="center">
  <img src="docs/images/Continuar%20de%20onde%20parou.png" alt="SUPER LIBRARY - Continuar jogo" width="100%">
</p>

Na próxima vez que o mesmo jogo for aberto, o launcher oferece a opção de continuar daquele ponto ou iniciar normalmente.

---

## O que é o SUPER LIBRARY?

O **SUPER LIBRARY** é uma interface independente para o **Snes9x** criada para transformar uma coleção de jogos de Super Nintendo em uma biblioteca visual simples de navegar.

Em vez de abrir o emulador, procurar ROMs em pastas e repetir configurações, o usuário pode navegar por capas em um carrossel, iniciar jogos por controle, mouse ou teclado, organizar a coleção, procurar capas ausentes, instalar ou selecionar o Snes9x e retornar ao launcher sem quebrar o fluxo da sessão.

A versão **v1.0.1** aprofunda essa proposta com **Quick Resume, Favoritos, Recentemente Jogados, busca instantânea, recuperação mais robusta do controle após sair do Snes9x e proteção adicional para saves e ROMs**.

> **Importante:** o SUPER LIBRARY **não inclui ROMs comerciais e não oferece download de ROMs**. Use somente jogos obtidos e mantidos de acordo com as leis aplicáveis na sua região.

---

## Download

Baixe sempre a versão mais recente pela página **Releases** deste repositório.

**Arquivo recomendado:** `SUPER_LIBRARY_Setup_v1.0.1.exe`

Se houver apenas um arquivo para baixar, escolha **o instalador**, e não o `SuperLibrary.exe` isolado da pasta de instalação.

### Requisitos

- Windows 10 ou Windows 11 **64-bit**
- Resolução recomendada: 1280×720 ou superior
- Controle USB ou Bluetooth opcional, reconhecido pelo Windows/SDL
- Internet apenas para recursos online, como instalar/atualizar Snes9x, shaders e procurar capas
- **Python não é necessário** no computador do usuário

---

## Destaques da v1.0.1

### Quick Resume

Ao retornar ao SUPER LIBRARY durante um jogo, é possível criar um **ponto de continuação** antes de fechar o Snes9x.

Na próxima vez que o mesmo jogo for aberto, o launcher oferece a opção de **continuar exatamente de onde você parou** ou iniciar normalmente.

Os pontos de continuação ficam organizados por jogo em:

```text
SUPER LIBRARY\
└── Snes9x\
    └── Saves\
        └── Quick Resume\
            └── Nome do jogo [identidade]\
                ├── resume.state
                └── info.json
```

O Quick Resume é separado do SRAM e dos save states comuns do usuário. O fluxo também aguarda o controle voltar ao estado neutro antes de devolver o input ao jogo, evitando que o botão usado para confirmar uma opção vire um comando dentro da emulação.

### Favoritos

Jogos podem ser marcados como favoritos e exibidos em uma visualização própria da biblioteca.

- `F2` — adiciona/remove o jogo selecionado dos Favoritos
- **L3** — faz o mesmo em controles SDL normalizados que possuem clique no analógico

Um jogo favoritado recebe uma estrela ao lado do título e permanece salvo entre sessões.

### Recentemente Jogados

O SUPER LIBRARY mantém uma lista persistente dos **30 jogos abertos mais recentemente**.

- `F3` — alterna entre **Todos → Favoritos → Recentemente Jogados**
- **R3** — faz o mesmo em controles SDL normalizados que possuem clique no analógico

### Busca instantânea

Pressione `Ctrl+F` e comece a digitar parte do nome do jogo. A biblioteca procura o melhor resultado em tempo real, o que facilita a navegação em coleções grandes.

### Controle mais robusto

O subsistema de controle foi revisado para melhorar o retorno ao launcher depois que o Snes9x fecha.

O bridge SDL possui estado de prontidão, heartbeat, reconexão e tratamento de hot-plug. O fechamento do Snes9x continua sendo solicitado de forma normal, sem force-kill, preservando o fluxo de gravação do emulador.

### Diagnóstico do controle

`F4` abre informações úteis para suporte, incluindo:

- nome do controle;
- reconhecimento SDL normalizado ou genérico;
- presença de L2/R2 quando mapeados;
- estado da conexão;
- saúde do bridge;
- tempo desde o último heartbeat;
- estado de bateria quando o driver realmente fornece essa informação.

### Último selecionado e último jogado

A posição em que o usuário estava navegando agora é armazenada separadamente do último jogo efetivamente aberto, evitando que simples navegação altere o histórico da sessão.

### Instância única

No Windows, o SUPER LIBRARY impede que duas interfaces principais sejam abertas ao mesmo tempo e disputem controle, música ou arquivos de configuração.

---

## Primeira configuração

1. Instale e abra o **SUPER LIBRARY**.
2. Clique em **SELECT** e escolha **Choose Folder** para apontar para sua pasta de ROMs, ou use **Import Collection** para criar uma biblioteca organizada a partir de uma coleção que você já possui.
3. Clique em **Y — SNES9X** e escolha **Download Snes9x and Shaders**.
   - Se você já possui Snes9x, escolha **Choose Existing**.
4. Aguarde a instalação/configuração do emulador e dos shaders.
5. Navegue pelos jogos e pressione **A / Cross** ou clique em **A — PLAY**.

Quando o Snes9x for fechado, o SUPER LIBRARY retorna automaticamente e restaura o controle do launcher.

---

## Retornar ao SUPER LIBRARY durante o jogo

O atalho se adapta ao tipo de controle conectado:

- **controle moderno:** segure **R2 / RT por aproximadamente 1,2 segundo**;
- **controle estilo SNES / sem gatilhos:** segure **START + SELECT por aproximadamente 1,2 segundo**.

Quando o Quick Resume está disponível, o jogo é pausado antes da caixa de decisão receber o input. Assim, direcional, analógicos e botões usados no menu não movimentam o personagem ou a câmera no jogo que está por trás.

O usuário pode então escolher entre:

- **Save & Exit** — cria o ponto de continuação e volta à biblioteca;
- **Exit Without Saving** — volta à biblioteca sem criar um novo ponto;
- **Return to Game** — cancela a saída e continua jogando.

R1/RB permanece livre para os comandos normais dos jogos durante gameplay.

---

## Controles — Gamepad

O programa usa a camada de controle do **SDL/pygame**. Controles reconhecidos como game controllers recebem mapeamento normalizado e o SUPER LIBRARY adapta seus atalhos ao dispositivo.

### Controles modernos

| Ação | Xbox / XInput | PlayStation | Função |
|---|---|---|---|
| Navegar | D-Pad ←/→ ou analógico esquerdo | D-Pad ←/→ ou analógico esquerdo | Jogo anterior / próximo |
| Jogar | **A** | **Cross (×)** | Abre o jogo selecionado |
| Voltar | **B** | **Circle (○)** | Volta / sai do fullscreen / fecha em janela quando aplicável |
| Smart Refresh | **X** | **Square (□)** | Atualiza e repara a biblioteca com correspondências de alta confiança |
| Snes9x Manager | **Y** | **Triangle (△)** | Instalar, atualizar, reparar ou selecionar Snes9x |
| Música | **LT** | **L2** | Liga/desliga a música do launcher |
| Página anterior | **LB** | **L1** | No launcher: volta 5 jogos |
| Próxima página | **RB** | **R1** | No launcher: avança 5 jogos |
| Favorito | **L3** | **L3** | Adiciona/remove o jogo dos Favoritos |
| Visualização | **R3** | **R3** | Todos → Favoritos → Recentemente Jogados |
| Sair do jogo | **RT — segurar ~1,2 s** | **R2 — segurar ~1,2 s** | Abre o fluxo de retorno ao SUPER LIBRARY |
| Configurar emulador | **Menu / Start** | **Options** | Abre Snes9x sem ROM para configuração |
| Fechar launcher | **View / Back** | **Share / Create** | Fecha o SUPER LIBRARY |

### Controles estilo SNES / sem L2 e R2

- **L1 / botão L** — liga/desliga a música do launcher;
- **START + SELECT segurados por aproximadamente 1,2 segundo** — abre o fluxo de retorno ao SUPER LIBRARY;
- os botões de ombro permanecem livres durante gameplay;
- recursos que exigem L3/R3 continuam disponíveis pelo teclado quando o controle não possui clique nos analógicos.

### Controles compatíveis

A compatibilidade depende de o dispositivo ser reconhecido pelo Windows e pelo SDL. O programa foi projetado para funcionar, em geral, com:

- Xbox 360 / Xbox One / Xbox Series e outros controles XInput;
- DualShock 4 e DualSense;
- controles 8BitDo em modos compatíveis com Windows;
- controles estilo SNES reconhecidos pelo SDL;
- muitos controles USB/Bluetooth genéricos.

Em controles genéricos sem mapeamento SDL conhecido, a posição dos botões pode variar. Hot-plug, desconexão e reconexão são tratados pelo launcher.

---

## Controles — Mouse

Todos os principais botões desenhados na interface são interativos:

| Elemento | Função |
|---|---|
| D-Pad esquerdo/direito | Navega pelo carrossel |
| **SELECT** | Abre o menu da biblioteca de ROMs |
| **START** | Abre o Snes9x sem jogo para configuração |
| **A — PLAY** | Inicia o jogo selecionado |
| **B — BACK** | Volta / sai do fullscreen / fecha o launcher |
| **X — REFRESH** | Executa o Smart Refresh |
| **Y — SNES9X** | Abre o Emulator Manager |
| LED vermelho/cinza | Pausa ou retoma a música |
| POWER | Fecha o SUPER LIBRARY |

---

## Atalhos de teclado

| Tecla | Ação |
|---|---|
| `←`, `A` ou `W` | Jogo anterior |
| `→`, `D` ou `↓` | Próximo jogo |
| `Enter`, `Return`, `Space` ou `S` | Jogar |
| `R` ou `X` | Smart Refresh |
| `F1` ou `Y` | Snes9x Manager |
| `F2` | Adicionar/remover Favorito |
| `F3` | Todos → Favoritos → Recentemente Jogados |
| `F4` | Diagnóstico do controle |
| `Ctrl+F` | Busca instantânea |
| `Esc`, `Backspace` ou `Q` | Voltar / fechar |
| `Page Up` | Volta 5 jogos |
| `Page Down` | Avança 5 jogos |
| `F11` | Alterna fullscreen |

---

## Biblioteca de ROMs

O botão **SELECT** abre o menu **ROM Library**.

### Choose Folder

Aponta diretamente para uma pasta existente com ROMs compatíveis.

### Import Collection

Importa uma coleção que **já pertence ao usuário** para uma biblioteca separada e organizada. O importador pode trabalhar com pasta, ROM solta, ZIP de um jogo e pacotes ZIP com múltiplos jogos.

Perfis disponíveis:

- **PT-BR**
- **Auto / Mixed**
- **USA**
- **Europe**
- **Japan**

A deduplicação é feita pelo conteúdo real da ROM, e não apenas pelo nome do arquivo. Variantes realmente diferentes — tradução, revisão ou região — são preservadas.

Depois de uma importação, o carrossel vai diretamente para a ROM instalada. Se esse jogo ainda não possuir arte, o SUPER LIBRARY pode procurar **somente a capa dele**, sem iniciar uma varredura completa da biblioteca.

### Scan This PC

Procura automaticamente uma pasta com ROMs SNES no computador e pede confirmação antes de usá-la.

### Create Organized Copy

Cria **cópias ZIP organizadas em outro diretório**. A coleção de origem permanece intacta.

### Find Missing Covers

Procura capas ausentes usando metadados e fontes online. O **LaunchBox Games Database é a fonte principal**, com validação de título e plataforma. Outras fontes são consultadas somente quando o LaunchBox não consegue fornecer uma correspondência adequada.

Capas existentes não são substituídas indiscriminadamente.

---

## Smart Refresh

O **X — REFRESH** é o mecanismo de manutenção da biblioteca.

Entre as tarefas que pode executar, sempre usando critérios de confiança elevados:

- recuperar nomes de capas reconhecidas pelo conteúdo;
- limpar duplicatas de capas reconhecidas;
- associar ROMs e capas por identidade, aliases, hashes e metadados;
- padronizar ROMs reconhecidas;
- converter ROMs soltas reconhecidas em ZIP validado;
- preservar conflitos e correspondências duvidosas em vez de adivinhar.

> **Atenção:** o Smart Refresh pode alterar fisicamente arquivos da biblioteca quando a correspondência é considerada segura. Se quiser uma opção totalmente não destrutiva, prefira **Create Organized Copy**.

---

## Snes9x Manager

O botão **Y — SNES9X** concentra o gerenciamento do emulador.

### Sem Snes9x configurado

- **Download Snes9x and Shaders** — instala a versão oficial atual e o pacote de shaders;
- **Choose Existing** — seleciona uma instalação de Snes9x que você já possui.

### Com instalação gerenciada

- verificar atualizações;
- instalar shaders ausentes;
- reparar a instalação;
- remover a instalação gerenciada;
- escolher outro Snes9x.

O SUPER LIBRARY consulta o repositório oficial do Snes9x e o projeto `libretro/slang-shaders` somente quando necessário. O aplicativo não desativa nem contorna proteções de segurança do Windows.

> **Atenção:** ao remover uma instalação gerenciada do Snes9x, os arquivos que pertencem àquela instalação podem ser removidos junto com ela. Faça backup do que desejar preservar.

---

## Saves, Quick Resume e backup na desinstalação

Os saves gerenciados ficam sob a árvore do Snes9x, incluindo os pontos de Quick Resume.

Ao desinstalar o SUPER LIBRARY, se existirem ROMs e/ou saves, o desinstalador pode criar **um único arquivo ZIP** no local escolhido pelo usuário.

O backup preserva uma estrutura diretamente reconhecível:

```text
Roms\...
Snes9x\Saves\...
```

Antes de prosseguir com a desinstalação, o backup é reaberto e verificado por:

- quantidade total de arquivos;
- caminho relativo de cada arquivo;
- tamanho exato;
- SHA-256 de cada ROM e save.

Se a verificação falhar, a desinstalação é cancelada e os arquivos originais permanecem intactos.

---

## Música e indicador de energia

A interface possui música ambiente própria. Ela pode ser ligada/desligada pelo controle compatível ou clicando no **LED** da interface, e a preferência fica salva para as próximas execuções.

- **controle moderno:** L2 / LT;
- **controle estilo SNES / sem gatilhos:** L1 / L;
- **mouse:** clique no LED.

A playlist é dinâmica: os arquivos `.ogg` incluídos na pasta de música da build entram automaticamente na reprodução. O launcher começa por uma faixa aleatória, percorre a playlist continuamente e preserva o crossfade entre as músicas.

Ao iniciar o Snes9x, a música do frontend é suspensa e retorna quando o usuário volta ao SUPER LIBRARY, respeitando a preferência salva.

---

## Principais recursos

- interface independente inspirada na estética do SNES americano;
- carrossel visual com capa, título e contador;
- títulos longos com rolagem automática;
- suporte a mouse, teclado e gamepad;
- hot-plug e reconexão de controles USB/Bluetooth;
- atalhos adaptativos para controles modernos e estilo SNES;
- Quick Resume com ponto de continuação por jogo;
- Favoritos e visualização de Recentemente Jogados;
- busca instantânea;
- diagnóstico de controle;
- informação de bateria quando fornecida pelo driver;
- recuperação robusta do controle ao voltar do Snes9x;
- último selecionado separado do último jogado;
- proteção de instância única;
- gerenciamento de Snes9x e shaders;
- suporte a instalação externa do Snes9x;
- importação e deduplicação exata de coleções;
- perfis PT-BR e internacionais;
- busca direcionada de capa para ROM recém-importada;
- criação de cópia organizada sem alterar a origem;
- Smart Refresh para manutenção da biblioteca;
- backup verificado de ROMs e saves durante a desinstalação;
- fullscreen;
- playlist dinâmica de música com crossfade e efeitos sonoros de interface;
- instalação autônoma: **o usuário não precisa instalar Python, PySide6 ou pygame**.

---

## Formatos de ROM reconhecidos

A biblioteca principal reconhece:

- `.zip`
- `.sfc`
- `.smc`
- `.fig`
- `.swc`

O importador também possui suporte de inspeção para alguns formatos/containers adicionais durante a organização. A capacidade de ler `.7z`/`.rar` pode depender das ferramentas disponíveis no Windows. ZIP é o formato recomendado.

---

## Solução de problemas

### O programa abre, mas não mostra jogos

Use **SELECT → Choose Folder** e escolha a pasta correta. Verifique se existem arquivos em formatos reconhecidos.

### Não tenho Snes9x

Use **Y → Download Snes9x and Shaders**. Também é possível selecionar uma instalação existente.

### O controle não responde

1. confirme que o Windows reconhece o controle;
2. tente reconectar via USB/Bluetooth;
3. use `F4` para consultar o diagnóstico do controle;
4. em controles genéricos, teste o modo XInput quando disponível.

### Quero sair do jogo sem pegar o mouse

- em controle moderno, segure **R2 / RT por cerca de 1,2 segundo**;
- em controle estilo SNES / sem gatilhos, segure **START + SELECT por cerca de 1,2 segundo**.

### Meu antivírus mostrou um alerta

Não desative sua proteção. Confirme que o instalador veio da página oficial **Releases** deste repositório e compare o SHA-256 publicado na release. Consulte também [SECURITY.md](SECURITY.md).

Mais respostas: [FAQ.md](FAQ.md)

---

## Privacidade e rede

O SUPER LIBRARY trabalha principalmente com arquivos locais. Conexões de rede são usadas para funções explicitamente relacionadas a conteúdo online, como:

- consultar/baixar Snes9x oficial;
- consultar/baixar shaders;
- procurar metadados e capas ausentes.

O programa não inclui um serviço de download de ROMs comerciais.

---

## Projeto independente

SUPER LIBRARY é um projeto independente e não é afiliado, patrocinado ou endossado pela Nintendo, pelo projeto Snes9x, pelo projeto libretro ou por outros detentores de marcas/conteúdo mencionados.

Nintendo, Super Nintendo, SNES e marcas relacionadas pertencem aos seus respectivos proprietários. Snes9x e slang-shaders são projetos de terceiros e permanecem sujeitos aos seus próprios termos/licenças.

Veja [NOTICE.md](NOTICE.md).

---

## Versão

### **v1.0.1 — Library & Resume Update**

A v1.0.1 amplia a experiência da primeira versão pública com Quick Resume, Favoritos, Recentemente Jogados, busca instantânea, diagnóstico de controle, retorno mais robusto do Snes9x e backup verificado de ROMs e saves.

[Changelog](CHANGELOG.md) · [Controles](CONTROLS.md) · [Guia rápido](QUICK_START.md) · [FAQ](FAQ.md)
