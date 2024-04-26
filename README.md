<div align="center">
  <h1>
      Problema 1: Tic-Tac-Toe
  </h1>

  <h3>
    Gabriel Cordeiro Moraes, 
    Georgenes Caleo Silva Pinheiro, 
    João Gabriel Lima Almeida, 
    João Pedro Silva Bastos
  </h3>

  <p>
    Engenharia de Computação – Universidade Estadual de Feira de Santana (UEFS)
    Av. Transnordestina, s/n, Novo Horizonte
    Feira de Santana – BA, Brasil – 44036-900
  </p>

  <center>gcmorais66@gmail.com, caleosilva75@gmail.com, gabriel.lima.almeida@gmail.com, joaopedro.silvabastos.splash@gmail.com</center>

</div>

# 1. Introdução

No cenário contemporâneo, a indústria de jogos eletrônicos emergiu como uma força cultural e econômica significativa, influenciando não apenas o entretenimento, mas também áreas como tecnologia, educação e saúde. Com o avanço da tecnologia e a crescente popularidade dos jogos, tornou-se imperativo compreender a importância dessa indústria e seu impacto global.

Embora aparentemente simples em sua mecânica, o jogo da velha oferece insights valiosos sobre estratégia, padrões e tomada de decisões, tornando-se uma metáfora poderosa para conceitos mais amplos, como competição, cooperação e resolução de problemas. Sua essência simples e seu estilo de jogo que atravessa o tempo ainda conquistam jogadores de todas as faixas etárias, oferecendo uma experiência de entretenimento descomplicada, porém envolvente.

Neste contexto, os alunos matriculados na disciplina TEC499 - MI Sistemas Digitais foram selecionados para criar um console que inclua uma versão do jogo da velha. Esta versão do jogo será executada em uma interface de texto, acessível através do terminal. A funcionalidade do jogo será voltada para permitir a interação de dois jogadores, possibilitando que cada jogador escolha onde marcar no tabuleiro a cada turno, e que a confirmação das jogadas seja feita por meio de um mouse conectado a uma das portas USB disponíveis no Kit de Desenvolvimento DE1-SoC.

# 2. Metodologia

### 2.1 - Sistema USB na DE1-SoC
A placa conta com duas entradas USB conectadas a um controlador de HUB de duas portas e a um controlador USB (USB3300), conforme a Imagem 1. O HUB USB funciona como um multiplicador de portas. Quando você conecta um hub USB a uma porta do computador, o hub em si se comunica com o controlador USB do computador para obter energia e informações sobre a porta.

Imagem 1: Mudulo USB na DE1-Soc <br/>
![Imagem 1](https://github.com/caleosilva/Sistemas-Digitais-Problema-1/blob/main/readme_images/image1.png)

O controlador USB por sua vez permite a comunicação entre dispositivos USB e o computador, gerenciando todas as funções que vão desde a detecção do dispositivo até a transferência de dados e energia e desempenha as seguintes funções:

   - **Detecção de dispositivos:**

      * Quando um dispositivo USB é conectado a uma porta do computador, o controlador USB inicia o processo de detecção.

      * Ele verifica se há sinal elétrico na porta USB, indicando a conexão de um dispositivo.

      * Em seguida, o controlador USB inicia o processo de enumeração, onde identifica o tipo de dispositivo conectado e verifica se está em conformidade com os padrões USB.

   - **Configuração do dispositivo:**
      
      * Após a detecção, o controlador USB configura o dispositivo.
      
      * Ele atribui um endereço único ao dispositivo para identificação durante a comunicação.
      
      * O controlador também estabelece a comunicação inicial com o dispositivo, iniciando um processo de handshaking para determinar os parâmetros de comunicação adequados.

   - **Gerenciamento de energia:**
      
      * O controlador USB fornece energia aos dispositivos conectados através das portas USB.
      
      * Ele monitora o consumo de energia de cada dispositivo e garante que não exceda os limites estabelecidos.
      
      * Em caso de dispositivos de baixa energia, o controlador pode ajustar dinamicamente a energia fornecida para otimizar a eficiência energética.

   - **Transferência de dados:**

      * Quando ocorre uma transferência de dados entre o computador e um dispositivo USB, o controlador USB gerencia todo o processo.
   
      * Ele controla o fluxo de dados, dividindo-os em pacotes que são transmitidos através do barramento USB.
   
      * O controlador garante que os pacotes sejam transmitidos corretamente e retransmite pacotes perdidos, se necessário, para garantir a integridade dos dados.
   
   - **Gestão de interrupções:**
      
      * Dispositivos USB podem enviar interrupções para indicar eventos importantes, como pressionar uma tecla em um teclado USB ou a inserção de um cartão de memória.
      
      * O controlador USB intercepta essas interrupções e as encaminha para o sistema operacional do computador.
      
      * O sistema operacional responde às interrupções apropriadas, executando as ações necessárias de acordo com o evento ocorrido.

   - **Suporte a protocolos:**
      
      * O controlador USB suporta vários protocolos e padrões USB, como USB 1.x, USB 2.0, USB 3.x, entre outros.

      * Ele garante a compatibilidade entre diferentes dispositivos e sistemas operacionais, traduzindo os comandos e dados entre o formato usado pelo dispositivo e o formato esperado pelo sistema.

Os terminais do controlador USB (Imagem 2) desempenham um papel fundamental na conectividade e na integração dos dispositivos, permitindo uma ampla gama de funcionalidades. Por esse motivo é importante destacar a função dos principais terminais do controlador USB:

Imagem 2: Controlador USB da placa. <br/>
![Imagem 2](https://github.com/caleosilva/Sistemas-Digitais-Problema-1/blob/main/readme_images/image2.png)

   - CPEN (Charge Pump Enable): O terminal CPEN é usado para habilitar ou desabilitar o circuito de bomba de carga (charge pump) no controlador USB. A bomba de carga é usada para gerar uma tensão interna necessária para a operação do controlador quando a tensão de alimentação externa é insuficiente. Quando o CPEN está ativo (geralmente em nível lógico alto), a bomba de carga é habilitada.

   - EXTVBUS (External VBUS): Este terminal é usado para detectar a presença de uma fonte de alimentação externa (VBUS) conectada ao controlador USB. Ele fornece uma indicação ao controlador sobre se a energia está sendo fornecida através de uma fonte externa. Isso é útil em cenários onde o dispositivo USB pode ser alimentado por diferentes fontes de energia.

   - VBUS (Voltage Bus): O terminal VBUS fornece energia ao controlador USB e aos dispositivos conectados a ele. Este é o terminal através do qual a tensão de alimentação do barramento USB (+5V) é fornecida ao controlador e aos dispositivos USB conectados.

   - DM (Data Minus): O terminal DM é uma das duas linhas de dados diferenciais usadas para comunicação de dados entre o controlador USB e os dispositivos conectados. Ele carrega os sinais de dados negativos em uma transmissão diferencial. Juntamente com o terminal DP, forma o par de linhas de dados usado no barramento USB.

   - DP (Data Plus): O terminal DP é a segunda linha de dados diferencial usada para comunicação de dados entre o controlador USB e os dispositivos conectados. Ele carrega os sinais de dados positivos em uma transmissão diferencial. Juntamente com o terminal DM, forma o par de linhas de dados usado no barramento USB.

   - ID (Identification): O terminal ID é usado em portas USB de dispositivos que suportam o modo de operação OTG (On-The-Go). Ele é usado para detectar a presença de acessórios OTG, como cabos adaptadores ou dispositivos periféricos. O ID é comumente usado para determinar se um dispositivo USB deve operar no modo host ou no modo periférico em uma conexão OTG.

   - DATA (Data): Este terminal é um termo genérico que se refere às linhas de dados (DM e DP) em um barramento USB. O termo "DATA" pode ser usado para indicar a transmissão de dados entre o controlador USB e os dispositivos conectados. Nas especificações USB, as linhas de dados são normalmente chamadas de D- (Data Minus) e D+ (Data Plus).

   - CLKOUT (Clock Out): Alguns controladores USB podem ter um terminal CLKOUT que fornece um sinal de clock para sincronizar operações dentro do controlador ou para outros dispositivos no sistema. Esse sinal de clock pode ser útil para sincronizar operações de transmissão de dados ou para outros fins de temporização.

   - NXT (Next): O terminal NXT pode ser usado em controladores USB que implementam um protocolo de comunicação serial síncrono, como o USB 2.0 High-Speed. Ele pode ser usado para indicar o próximo bit ou byte de dados a ser transmitido ou recebido.

   - DIR (Direction): O terminal DIR pode ser usado em controladores USB para indicar a direção da transmissão de dados. Ele pode ser usado para controlar se os dados estão sendo transmitidos do controlador para o dispositivo (transmissão de saída) ou do dispositivo para o controlador (transmissão de entrada).

   - STP (Stop): O terminal STP pode ser usado em controladores USB para indicar o fim de uma transmissão de dados ou para sinalizar a parada de um dispositivo. Em alguns casos, pode ser usado para sinalizar a conclusão de uma transmissão de dados.

   - RESET (Reset): O terminal RESET é usado para reiniciar o controlador USB em caso de falha ou para redefinir sua configuração para o estado padrão. Ele pode ser usado para reiniciar o controlador USB em caso de erros de comunicação ou para limpar qualquer estado de erro persistente.

   - X1 (Crystal Input): O terminal X1 é usado para conectar um cristal de oscilação externo ao controlador USB. Esse cristal de oscilação é usado como fonte de clock para o controlador USB, garantindo que as operações de temporização sejam precisas e estáveis.

### 2.2 - Funcionamento Utilizando Mouse USB e Sistema Operacional (Linux)

- Conexão do mouse: Quando você conecta o mouse ao computador através da porta USB, o sistema operacional detecta a conexão física.

- Identificação do dispositivo: O sistema operacional consulta o mouse para identificar seu tipo e modelo. Isso é feito usando protocolos padrão de comunicação USB. O mouse envia informações que permitem ao sistema operacional reconhecê-lo como um dispositivo de entrada.

- Driver do mouse: O sistema operacional carrega o driver específico para o mouse conectado. Este driver é um pequeno software que permite que o sistema operacional entenda como se comunicar com o mouse e interprete os dados que ele envia.

- Recepção dos dados: Quando você move o mouse ou pressiona seus botões, ele gera sinais elétricos correspondentes aos movimentos e às interações. Estes sinais são convertidos em dados digitais pelo hardware do próprio mouse.

- Transferência para o controlador USB: Os dados digitais são então transferidos do mouse para o controlador USB do computador através do cabo USB.

- Interpretação pelo driver: O controlador USB envia os dados recebidos para o sistema operacional, que os encaminha para o driver específico do mouse. O driver é responsável por interpretar esses dados e convertê-los em ações compreensíveis para o sistema operacional.

- Tradução dos dados: Os dados enviados pelo mouse geralmente incluem informações sobre o movimento (por exemplo, a velocidade e a direção do movimento) e o estado dos botões (se estão pressionados ou não). O driver traduz esses dados em comandos que o sistema operacional pode entender e processar.

- Processamento pelo sistema operacional: Com base nos dados recebidos do driver do mouse, o sistema operacional executa as ações correspondentes. Por exemplo, se você mover o mouse para a direita, o sistema operacional atualiza a posição do ponteiro na tela. Se você pressionar um botão do mouse, o sistema operacional executa a ação associada a esse botão, como selecionar um item ou abrir um programa.

- Feedback ao usuário: Dependendo das configurações do sistema operacional e do driver do mouse, pode haver também um feedback ao usuário. Por exemplo, ao clicar em um botão do mouse, o sistema operacional pode produzir um som de clique ou exibir um efeito visual para indicar que a ação foi realizada com sucesso.

- Feedback ao mouse: O sistema operacional pode enviar comandos de feedback ao mouse, se necessário. Por exemplo, ao mover o ponteiro do mouse na tela, o sistema operacional pode enviar informações de configuração ao mouse para ajustar sua sensibilidade ou outras características.

### 2.3 - Funcionamento Utilizando Mouse USB Sem Uso de Sistema Operacional

Nesse cenário, o desenvolvimento de software é frequentemente realizado diretamente no nível de código de baixo nível, utilizando linguagens como C ou Assembly, e os desenvolvedores precisam ter um entendimento profundo dos protocolos e especificações USB para implementar a comunicação de forma eficaz. De maneira geral:

   - Conexão física: Quando o dispositivo USB é conectado ao computador, a detecção da conexão física é realizada diretamente pelo hardware do computador. Isso pode envolver a ativação de linhas de alimentação e detecção de sinais de dados.

   - Identificação do dispositivo: O dispositivo USB inicia seu processo de inicialização, onde ele se identifica ao computador. Isso geralmente envolve o envio de pacotes de configuração padrão USB que contêm informações sobre o fabricante, o tipo de dispositivo e outras características.

   - Enumeração USB: Após a identificação, o dispositivo solicita a enumeração USB, onde ele é atribuído a um endereço único pelo host (o computador) e a comunicação é configurada. No lado do host, o hardware USB responde à solicitação de enumeração e estabelece a comunicação bidirecional com o dispositivo.

   - Configuração de comunicação: Uma vez concluída a enumeração, o dispositivo e o computador configuram os canais de comunicação USB necessários para a troca de dados. Isso envolve a negociação de parâmetros de comunicação, como taxa de transferência e protocolo de comunicação.

   - Estabelecimento da conexão: Após a configuração da comunicação, o dispositivo e o computador estão prontos para iniciar a troca de dados. Eles estabelecem canais de comunicação bidirecionais através dos quais os dados serão transmitidos.

   - Troca de pacotes USB: A comunicação entre o dispositivo e o computador ocorre através da troca de pacotes USB. O dispositivo envia pacotes contendo dados, comandos ou informações de controle, e o computador os recebe e processa.

   - Interpretação de pacotes: No lado do computador, o hardware USB ou um controlador USB dedicado recebe os pacotes USB do dispositivo, decodifica-os e os encaminha para o destino apropriado. Isso pode envolver a identificação do tipo de pacote (por exemplo, pacote de dados, pacote de controle) e o encaminhamento dos dados para o processamento subsequente.

   - Resposta e Feedback: O computador pode enviar pacotes de resposta de volta ao dispositivo, confirmando o recebimento de dados, solicitando mais informações ou executando outras ações conforme necessário. Isso completa o ciclo de comunicação entre o dispositivo e o computador.

A inicialização e a comunicação de baixo nível são gerenciadas diretamente pelo hardware do computador e pelo firmware do dispositivo USB, sem a intervenção de um sistema operacional. Isso requer um entendimento profundo dos protocolos e especificações USB para implementar a comunicação de forma eficaz.

### 2.4 - Código

Para alcançar os objetivos propostos pelo problema, o código desenvolvido foi pensado para cumprir dois papeis importantes: Pegar as entradas dos dispositivos de entrada (neste caso, apenas o mouse) e utilizar esses dados para controlar o jogo da velha. 
Como dito anteriormente, o linux já trata as informações enviadas de dispositivos de entrada para o controlador USB, para se comunicar com esses dispositivos é necessário acessar o arquivo especial de caractere daquele dispositivo. Para isso, basta abrir o arquivo de dispositivo correspondente dentro do diretório "/dev/input/", no caso do mouse, o arquivo é o "/dev/input/mice". Apesar de ser aberto como um arquivo, esses dispositivos de caractere são na verdade interfaces de baixo nível que você pode ler o descritor retornado pela função de abertura e acessar os dados que aquele dispositivo está fornecendo. 

- **Thread de monitoramento do mouse**
  
Afim de monitorar corretamente o mouse sem que a sua leitura atrapalhe ou seja atrapalhada pela execução da lógica do jogo, foi criada uma thread chamada "threadMouse" para cuidar especificamente da leitura das entradas do mouse. Essa thread faz o seguinte procediemnto: 
- Primeiro ela abre o arquivo especial de caractere do mouse utilizando a função open() e guarda o descritor de arquivo retornado pela função em uma variável.
- Em seguida, verifica se esse descritor é igual a -1 (ou seja, não foi aberto corretamente) e entra em um looping de leitura.
- O terceiro passo, no looping de leitura, é utilizar a função read() para ler o descritor e armazenar os dados lidos em um array do tipo signed char de tamanho 3, ou seja, um array de 3 bytes que guardam valores de -127 a 127.
- O proximo passo é a interpretação dos dados, os bytes de indice 1 e 2 do array são respectivamente os valores de deslocamento no eixo X e Y do mouse, já o byte 0 guarda o valor do botão que está sendo pressionado no momento, que pode ser diferenciado entre eles fazendo um AND com valor do byte 0 e o código do botão.
- O ultimo passo realizado é a normalização dos valores de deslocamento, como o jogo não precisa de uma grande precisão como no caso de um ponteiro e sim a detecção do movimento direcional para mudar qual casa está sendo selecionada, realizamos uma normalização do deslocamento do mouse fixando o valor em -1, 0 ou 1 e considerando apenas o eixo em que o movimento teve maior magnitude.
  
Vale ressaltar que as variáveis dos botões e do deslocalmento no eixo X e Y (já normalizados) são globais para que possam ser acessadas em todo o programa em diferentes partes quando necessário. Seguindo os passos descritos, a função cumpre seu papel de a todo momento capturar as interações do mouse e salva-las de forma que possam ser utilizadas na execução do jogo. 

- **Linha de execução principal e lógica do jogo**

O jogo foi pensado para funcionar da seguinte forma: O jogador utiliza o movimento do mouse para selecionar um dos 9 quadrantes do tabuleiro e o botão esquerdo para marcar o quadrante (caso esteja vazio), mudando imediatamente a vez para o proximo jogador até que alguem vença ou ocorra um empate. É possivel também, a qualquer momento, pausar o jogo. No código, o tabuleiro foi representado por uma matriz 3x3 de caracteres, a posição em que o jogador está selecionado no momento é dada por uma struct "InputMouse" que guarda a informação de linha e coluna. As funções desenvolvidas e utilizadas foram:
- definir_linha_coluna(InputMouse): Utiliza o deslocamento do mouse para incrementar ou diminuir os valores de linha e coluna dentro da struct InputMouse, ou seja, utiliza o mouse para mover a seleção entre os quadrantes representados pelas posições da matriz.
- escolher_quadrante(InputMouse): Verifica se houve click no botão esquerdo e, caso tenha, realiza a jogada na posição selecionada.
- verificar_vencedor() e verificar_empate(): Percorrem a matriz nas linhas, colunas e diagonais para verificar se há condição de vitória ou empate.
- colocar_simbolo(linha, coluna, simbolo): Verifica se a posição selecionada já está ocupada por um X ou O (mostrando uma mensagem de posição inválida, caso esteja) e insere o simbolo do jogador atual na posição caso esteja vazia.
- inicializar_tabuleiro(): Reinicializa a matriz do tabuleiro preenchendo-na com caracteres de espaço vazio.
- No looping principal do main, cada vez em que ocorre um movimento no mouse ou algum botão é acionado, é printada na tela o tabuleiro e as informações de quem é o jogador da vez e qual o quadrante está sendo selecionado.
- Também no looping principal do main há uma verificação se o botão direito foi apertado o que realiza um toggle no valor da variavel "pauseGame", impedindo a execução da lógica do jogo e mantendo-o pausado até que o botão seja pressionada novamente.

# 3. Resultados

A inicialização do jogo da velha é simples: ao abrir o programa, o jogador é recebido com uma tela inicial intuitiva (Figura 1), onde basta clicar no botão do meio do mouse para começar. Uma vez iniciado, o jogo exibe informações cruciais no terminal: a vez do jogador (representado por X ou O), juntamente com as coordenadas linha x coluna, e o tabuleiro em si, com destaque em vermelho para indicar o quadrante a ser selecionado (Figura 2).

Figura 1: Tela inicial de boas vindas.
<br />
![Figura 1](https://github.com/caleosilva/Sistemas-Digitais-Problema-1/blob/main/readme_images/bemVindo.jpeg)

Figura 2: Tela principal do jogo em execução.
<br />
![Figura 2](https://github.com/caleosilva/Sistemas-Digitais-Problema-1/blob/main/readme_images/telaInicial.jpeg)


Essas indicações são essenciais para indicar visualmente ao jogador onde o cursor de seleção de quadrante está, já que não é uma interface de texto acessada via SSH, ou seja, não há cursor nativo. Como descrito na seção anterior, o movimento desse cursor (aqui representado por um * vermelho) é feito com base na direção do deslocamento do mouse desconsiderando movimentos menores no outro eixo, ou seja, caso o movimento seja feito na vertical com um pequeno movimento horizontal, apenas o movimento vertical vai ser contabilizado a fim de inibir movimentações acidentais devido a alta precisão do mouse.

Uma vez iniciado o jogo, o jogador pode realizar a jogada utilizando o botão esquerdo do mouse para marcar o quadrante selecionado (caso esteja vazio) ou pode pausar o jogo utilizando o botão direito. Uma vez pausado, aparecerá uma indicação de que o jogo está pausado e o jogador se torna incapaz de realizar qualquer outra operação (seja mover o mouse ou realizar jogada) até que o botão direito seja novamente pressionado.

A cada clique com o botão esquerdo, funções são acionadas para garantir o correto funcionamento da lógica do jogo. Estas funções verificam se o quadrante selecionado está livre para ser preenchido (Figura 3) e, caso positivo, insere o símbolo correspondente à vez do jogador (X ou O). Posteriormente, são verificadas as condições de vitória ou empate para determinar se o jogo deve acabar, voltando para a tela inicial como indicado na imagem (Figura 4).

Figura 3: Mensagem ao verificar se o quadrante está livre ou não.
<br />
![Figura 3](https://github.com/caleosilva/Sistemas-Digitais-Problema-1/blob/main/readme_images/posicaoOcupada.jpeg)


Figura 4: Tela após o jogador X ganhar.
<br />
![Figura 4](https://github.com/caleosilva/Sistemas-Digitais-Problema-1/blob/main/readme_images/vitoria.jpeg)

A respeito do funcionamento geral do mouse, a thread responsável por cuidar de suas entradas descrita e implementada na seção anterior permite que o movimento seja fluido e sutil, podendo o jogador realizar movimentos de diferentes graus de intensidade sem perder o controle de onde está o cursor. Uma das coisas que permitiu esse controle foi a adição de um pequeno sleep após o movimento para que o jogador tenha tempo de ver o movimento e reagir a ele, ou seja, ele não pule casas de forma não intencional (ex: ir da 1 direto para a 3 quando queria na verdade parar na 2);

# 4. Conclusão

Após concluir o projeto, foi possível aprofundar o entendimento sobre a interação entre hardware e software, especificamente entre o mouse, a placa DE1-SoC e o programa desenvolvido em C no sistema operacional Linux. Durante a manipulação da placa, foi explorado seus princípios básicos e suas interfaces, compreendendo o funcionamento da comunicação entre o hardware do mouse, controlador USB, interrupções e como o linux disponibiliza esses dados. Além disso, foram descobertas as vantagens do uso do makefile para otimizar e simplificar o processo de compilação.

É importante destacar que todos os requisitos propostos pelo problema foram atendidos com sucesso. O jogo está sendo executado em uma interface de texto, acessível através do terminal, permitindo a interação entre dois jogadores, sendo controlado exclusivamente por um mouse conectado a uma das portas USB da placa e permitindo que os jogadores possam, além de jogar, pausar o jogo e inicia-lo.

No entanto, há espaço para melhorias. Uma expansão da interface do jogo para ocupar toda a tela proporcionaria uma experiência mais imersiva, além disso, implementar um cursor mais preciso poderia ser interessante no sentido de adicionar novos elementos clicáveis na tela, permitindo uma precisão que vai além dos 9 quadrantes do tabuleiro.

# Referências
  * USB3300 DataSheet: Disponível em: https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ProductDocuments/DataSheets/00001783C.pdf. Acesso em: 10 de mar. de 2024.
  * Using input devices on embedded Linux demo: USB mouse on Intel Edison: Disponível em: https://www.microcontrollertips.com/using-input-devices-on-embedded-linux-usb-mouse-on-intel-edison/. Acesso em 05 de mar. de 2024. 
