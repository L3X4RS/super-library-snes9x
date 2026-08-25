# Changelog

## v1.0.3 — Current Stable Line

A v1.0.3 consolida a experiência atual do SUPER LIBRARY para Snes9x.

### Quick Menu em jogo
- R3 abre o Quick Menu em controles modernos;
- START + SELECT abre o mesmo Quick Menu em controles clássicos/sem R3;
- R2/RT permanece livre durante gameplay;
- o jogo é pausado enquanto o overlay está ativo;
- o input só é devolvido ao jogo depois que o controle volta ao estado neutro.

### Progresso
- SAVE PROGRESS cria um checkpoint manual por jogo;
- LOAD PROGRESS carrega o checkpoint existente;
- CONTINUE PLAYING? aparece apenas quando o jogador usou SAVE PROGRESS;
- RETURN TO LIBRARY não cria save automático;
- Save Points ficam separados dos slots normais do Snes9x.

### Video Filters
- navegação de shaders durante o jogo;
- preview ao vivo quando o build do Snes9x é validado com segurança;
- aplicação/cancelamento sem precisar navegar pela interface nativa do emulador;
- bridge fail-closed: se a estrutura esperada não puder ser validada, nenhuma alteração é tentada por adivinhação.

### Controller Settings em jogo
- remapeamento do Player 1 pelo Quick Menu em builds compatíveis do Snes9x;
- captura pelo mesmo caminho WinMM usado pelo port Windows do Snes9x;
- cancelamento restaura o mapeamento anterior;
- integração indisponível quando o build não pode ser reconhecido com segurança.

### Biblioteca
- biblioteca gerenciada final em `Snes9x\Roms`;
- migração de layouts anteriores preservando histórico, favoritos e progresso;
- organização física em `Standard\USA|Europe|Japan|Other`, `Translations\PT-BR` e `MSU-1`;
- importação da coleção do próprio usuário sem modificar a origem;
- deduplicação pelo payload real;
- preservação de regiões, revisões e traduções realmente diferentes;
- ZIPs de uma ROM validados para jogos comuns;
- tratamento específico de pacotes MSU-1.

### Biblioteca visual
- Favoritos persistentes;
- Recentemente Jogados com até 30 entradas;
- filtros Todos / Favoritos / Recentes;
- busca instantânea;
- último jogo jogado separado da simples seleção/navegação.

### Controles
- bridge SDL isolado da interface Qt;
- USB/Bluetooth;
- hot-plug e reconexão;
- diagnóstico de controle;
- L3 adiciona/remove Favorito no launcher;
- R3 alterna a visualização da biblioteca no launcher e abre o Quick Menu durante gameplay.

### Snes9x Manager
- download da release Windows oficial do Snes9x;
- instalação de slang-shaders;
- escolha de Snes9x existente;
- atualização, reparo e remoção gerenciada;
- preservação da pasta de ROMs antes de manutenção destrutiva;
- arquivo de procedência/hashes do emulador gerenciado para verificação.

### Capas e Smart Refresh
- LaunchBox Games Database como fonte principal;
- aliases, hashes, metadados e fallbacks controlados;
- Smart Refresh conservador para nomes, duplicatas e padronização;
- conflitos e correspondências de baixa confiança são preservados em vez de adivinhados.

### Áudio e interface
- playlist interna dinâmica;
- descoberta automática das faixas OGG incluídas na build;
- faixa inicial aleatória;
- crossfade entre músicas;
- música suspensa durante gameplay e retomada no retorno;
- efeitos sonoros e indicador visual.

### Distribuição
- Windows 10/11 64-bit;
- Python não é necessário para o usuário final;
- repositório público continua destinado a documentação e releases binárias;
- SHA-256 e GitHub Artifact Attestation fazem parte do fluxo de publicação.

---

## v1.0.0 — First Public Stable Release

Primeira versão pública estável do SUPER LIBRARY.

### Interface
- interface independente inspirada no Super Nintendo;
- carrossel de biblioteca;
- títulos longos com marquee;
- contador de jogos;
- fullscreen;
- música, efeitos de interface e LED interativo.

### Controles
- mouse;
- teclado;
- gamepads SDL/XInput;
- suporte USB/Bluetooth e reconexão;
- atalhos adaptativos conforme o tipo de controle;
- START/Options abre o Snes9x em modo de configuração.

### Música
- playlist dinâmica;
- descoberta automática de arquivos `.ogg` incluídos na build;
- faixa inicial aleatória;
- reprodução contínua com crossfade;
- música suspensa durante o Snes9x e retomada ao voltar ao frontend.

### Capas
- LaunchBox Games Database como fonte principal;
- validação de título e plataforma;
- fontes alternativas somente quando necessário;
- busca de capas ausentes integrada à manutenção da biblioteca.

### Snes9x
- instalação gerenciada opcional do Snes9x oficial;
- slang-shaders;
- escolha de emulador existente;
- atualização, reparo e remoção gerenciada;
- retorno automático ao frontend após fechar o emulador.

### Biblioteca
- seleção manual de pasta;
- scan automático do PC;
- importação de coleção;
- deduplicação por payload;
- perfis de região/idioma;
- cópia organizada não destrutiva;
- busca de capas ausentes;
- Smart Refresh.

### Distribuição
- instalador Windows 64-bit;
- usuário final não precisa instalar Python;
- numeração pública iniciada em v1.0.0.
