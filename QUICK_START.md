# SUPER LIBRARY v1.0.3 — Guia rápido

## 1. Instale

Baixe o instalador da **v1.0.3** pela página **Releases** e conclua a instalação.

> Use o Setup completo da release. Não copie somente o `SuperLibrary.exe` de outra instalação.

## 2. Escolha sua biblioteca

Abra o programa e use **SELECT → Choose Folder** para apontar para uma pasta existente de ROMs compatíveis.

Também é possível usar **Import Collection** para criar uma biblioteca gerenciada e organizada a partir de arquivos que você já possui.

## 3. Configure o Snes9x

Use **Y — SNES9X**.

- **Download Snes9x and Shaders**: baixa/instala o Snes9x oficial e slang-shaders;
- **Choose Existing**: usa um Snes9x já existente.

## 4. Jogue

Navegue com D-Pad/analógico ou mouse e pressione:

- **A / Cross** no controle; ou
- **A — PLAY** com o mouse; ou
- `Enter` / `Space` no teclado.

## 5. Abra o Quick Menu durante o jogo

### Controle moderno

Pressione **R3**.

### Controle clássico / sem R3

Pressione **START + SELECT juntos**.

R2/RT permanece livre para o jogo.

## 6. Use o Quick Menu

O menu oferece:

- **RESUME GAME** — volta ao jogo;
- **SAVE PROGRESS** — cria um checkpoint manual daquele jogo;
- **LOAD PROGRESS** — carrega o checkpoint existente;
- **VIDEO FILTERS** — navega pelos shaders/filtros durante a sessão;
- **CONTROLLER SETTINGS** — remapeia o Player 1 quando a integração com o build do Snes9x pode ser validada;
- **RETURN TO LIBRARY** — fecha o Snes9x e volta à biblioteca.

**RETURN TO LIBRARY não salva automaticamente.**

Se você usou **SAVE PROGRESS**, na próxima abertura daquele jogo o SUPER LIBRARY oferece **CONTINUE PLAYING?** com as opções de continuar do save, iniciar normalmente ou cancelar.

## Atalhos essenciais no launcher

| Controle | Ação |
|---|---|
| D-Pad/analógico ←/→ | navegar |
| A / Cross | jogar |
| B / Circle | voltar |
| X / Square | Smart Refresh |
| Y / Triangle | Snes9x Manager |
| L2 / LT | música |
| L1 / LB | -5 jogos |
| R1 / RB | +5 jogos |
| L3 | Favorito |
| R3 | Todos → Favoritos → Recentemente Jogados |
| Start / Options | configurar Snes9x |

Durante gameplay, R3 muda de contexto e abre o Quick Menu.

## Biblioteca gerenciada

Quando você usa Import Collection, a organização pode ficar assim:

```text
Snes9x\Roms\
├── Standard\USA
├── Standard\Europe
├── Standard\Japan
├── Standard\Other
├── Translations\PT-BR
└── MSU-1
```

A coleção original não é modificada pelo processo de importação.

## Segurança

Baixe apenas da página oficial Releases e confira o SHA-256 publicado junto com a release final.

Para a lista completa de controles e recursos, veja:

- [CONTROLS.md](CONTROLS.md)
- [FEATURES.md](FEATURES.md)
- [FAQ.md](FAQ.md)
