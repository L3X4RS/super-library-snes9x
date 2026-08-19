# FAQ — SUPER LIBRARY

## Preciso instalar Python?
**Não.** A distribuição final leva o runtime necessário. O usuário não precisa instalar Python, PySide6, pygame ou pip.

## O programa inclui ROMs?
**Não.** SUPER LIBRARY não distribui nem oferece catálogo de download de ROMs comerciais.

## O programa inclui Snes9x dentro do instalador?
O frontend permite instalar o Snes9x oficial sob demanda. O download acontece quando o usuário escolhe **Download Snes9x and Shaders**. Também é possível escolher uma instalação existente.

## Preciso de internet para jogar?
Não, depois que sua biblioteca e o Snes9x estão configurados. Internet é necessária para funções como instalação/atualização gerenciada do emulador, shaders e busca de capas.

## Posso usar meu próprio Snes9x?
Sim. Abra **Y — SNES9X → Choose Existing**.

## Como configuro vídeo, áudio e controles do Snes9x?
Pressione **START / Options / Menu** no launcher. O Snes9x abre sem uma ROM para você acessar suas configurações. Pressione o mesmo controle novamente para fechá-lo.

## Como volto ao SUPER LIBRARY durante um jogo?
O atalho se adapta ao tipo de controle:

- **controle moderno:** segure **R2 / RT por aproximadamente 1,2 segundo**;
- **controle estilo SNES / sem L2 e R2:** segure **START + SELECT por aproximadamente 1,2 segundo**.

O Snes9x será fechado e o SUPER LIBRARY voltará à frente.

## O R1/RB continua livre nos jogos?
Sim. R1/RB não é mais usado para fechar o Snes9x durante gameplay. No launcher, ele continua disponível para avanço rápido na biblioteca quando aplicável.

## Como funciona o controle da música?
Em controles modernos com gatilhos, use **L2 / LT**. Em controles estilo SNES ou sem gatilhos, use **L1 / L**. Também é possível clicar no LED da interface.

## Posso usar DualSense / DualShock?
O frontend usa SDL. DualShock 4 e DualSense normalmente são expostos como controles padrão no Windows/SDL, por USB ou Bluetooth. A experiência exata pode variar de acordo com driver, conexão e mapeamento do sistema.

## Posso usar controle Xbox?
Sim, controles XInput são o cenário mais direto de compatibilidade.

## E controles genéricos?
Podem funcionar via fallback de joystick. A ordem dos botões pode variar dependendo do dispositivo. Se o controle oferecer modo XInput, esse modo é recomendado.

## O que o Smart Refresh altera?
Ele pode alterar arquivos quando uma correspondência é considerada de alta confiança: corrigir nomes de capas, remover duplicatas reconhecidas, padronizar ROMs e converter ROMs soltas em ZIP validado. Conflitos e casos duvidosos são preservados.

## Quero organizar sem alterar minha pasta original.
Use **SELECT → Create Organized Copy**. Essa função grava em outro diretório e deixa a coleção original intacta.

## O importador remove traduções ou revisões diferentes?
Não por nome. A deduplicação é baseada no payload real. Se duas ROMs tiverem conteúdo diferente, variantes como traduções, regiões e revisões podem coexistir.

## Como funciona a busca de capas?
O SUPER LIBRARY prioriza o **LaunchBox Games Database** para correspondências confiáveis de capas frontais e usa outras fontes somente quando o LaunchBox não consegue fornecer uma correspondência adequada.

## A música aceita mais de duas faixas?
Sim. A playlist é dinâmica: todos os arquivos `.ogg` incluídos na pasta de música da build entram na reprodução automática. O launcher inicia por uma faixa aleatória e segue continuamente com crossfade entre as músicas.

## Meu antivírus alertou sobre o programa. O que faço?
Não desative o antivírus. Verifique se o instalador foi obtido da página oficial Releases deste repositório e confira o SHA-256 publicado. Softwares novos/sem reputação suficiente podem gerar alertas heurísticos. Veja [SECURITY.md](SECURITY.md).

## Onde encontro relatórios de diagnóstico?
Dependendo da função usada, o programa pode gerar arquivos como:
- `managed_install_report.json`;
- `rom_import_report.json`;
- `smart_refresh_report.json`;
- relatórios de busca/correspondência de capas.

Eles são úteis ao abrir uma issue.
