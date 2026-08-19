# Changelog

## v1.0.0 — First Public Stable Release

Primeira versão pública estável do SUPER LIBRARY.

### Interface
- interface independente inspirada no Super Nintendo;
- carrossel de biblioteca;
- títulos longos com marquee;
- contador de jogos;
- fullscreen;
- música, efeitos de interface e LED interativo;
- D-Pad visual sem efeito de afundamento/deslocamento ao clicar.

### Controles
- mouse;
- teclado;
- gamepads SDL/XInput;
- suporte USB/Bluetooth e reconexão;
- atalhos adaptativos conforme o tipo de controle;
- em controles modernos, L2/LT controla a música;
- em controles modernos, R2/RT segurado por aproximadamente 1,2 s fecha o Snes9x e retorna;
- em controles estilo SNES/sem gatilhos, L1/L controla a música;
- em controles estilo SNES/sem gatilhos, START + SELECT segurados por aproximadamente 1,2 s fecham o Snes9x e retornam;
- R1/RB permanece livre durante gameplay;
- START/Options abre o Snes9x em modo de configuração.

### Música
- playlist dinâmica;
- descoberta automática de todos os arquivos `.ogg` incluídos na pasta de música da build;
- faixa inicial aleatória;
- reprodução contínua com crossfade entre faixas;
- música suspensa durante o Snes9x e retomada ao voltar ao frontend.

### Capas
- LaunchBox Games Database como fonte principal;
- validação de título e plataforma;
- uso de fontes alternativas somente quando o LaunchBox não fornece uma correspondência adequada;
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
- perfis PT-BR/International;
- cópia organizada não destrutiva;
- busca de capas ausentes;
- Smart Refresh.

### Distribuição
- instalador Windows 64-bit;
- usuário final não precisa instalar Python;
- numeração pública iniciada em v1.0.0.
