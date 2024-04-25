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

  <center>gcmorais66@gmail.com</center>

</div>

# 1. Introdução

No cenário contemporâneo, a indústria de jogos eletrônicos emergiu como uma força cultural e econômica significativa, influenciando não apenas o entretenimento, mas também áreas como tecnologia, educação e saúde. Com o avanço da tecnologia e a crescente popularidade dos jogos, tornou-se imperativo compreender a importância dessa indústria e seu impacto global.

Embora aparentemente simples em sua mecânica, o jogo da velha oferece insights valiosos sobre estratégia, padrões e tomada de decisões, tornando-se uma metáfora poderosa para conceitos mais amplos, como competição, cooperação e resolução de problemas. Sua essência simples e seu estilo de jogo que atravessa o tempo ainda conquistam jogadores de todas as faixas etárias, oferecendo uma experiência de entretenimento descomplicada, porém envolvente.

Neste contexto, os alunos matriculados na disciplina TEC499 - MI Sistemas Digitais foram selecionados para criar um console que inclua uma versão do jogo da velha. Esta versão do jogo será executada em uma interface de texto, acessível através do terminal. A funcionalidade do jogo será voltada para permitir a interação de dois jogadores, possibilitando que cada jogador escolha onde marcar no tabuleiro a cada turno, e que a confirmação das jogadas seja feita por meio de um mouse conectado a uma das portas USB disponíveis no Kit de Desenvolvimento DE1-SoC.

# 2. Metodologia

### 2.1 - Sistema USB na DE1-SoC
A placa conta com duas entradas USB conectadas a um controlador de HUB de duas portas e a um controlador USB (USB3300), conforme a Imagem 1. O HUB USB funciona como um multiplicador de portas. Quando você conecta um hub USB a uma porta do computador, o hub em si se comunica com o controlador USB do computador para obter energia e informações sobre a porta.

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

![Imagem 2](https://github.com/caleosilva/Sistemas-Digitais-Problema-1/blob/main/readme_images/image2.png)

   -CPEN (Charge Pump Enable): O terminal CPEN é usado para habilitar ou desabilitar o circuito de bomba de carga (charge pump) no controlador USB. A bomba de carga é usada para gerar uma tensão interna necessária para a operação do controlador quando a tensão de alimentação externa é insuficiente. Quando o CPEN está ativo (geralmente em nível lógico alto), a bomba de carga é habilitada.

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

# 3. Resultados
Ao iniciar o sistema, é solicitado do usuário o endereço IP da sua máquina na rede (nesta versão todos o protótipo "escuta" sempre na porta 5555). Em seguida, é possível acessar um menu interativo com cinco opções: [1] para enviar mensagens, [2] para visualizar as mensagens recebidas e [3] para acionar o bot de teste, [4] para salvar a lista de mensagem confirmadas em um arquivo em .txt e [5] para sair. Conforme a imagem abaixo:

![Menu principal.](https://github.com/bielcmoraes/Concorrencia-e-Conectividade-Problema-3/blob/main/readme_images/menu_principal.png)

É importante salientar que as funcionalidades de sincronização incial do sistema (a sincronização inicial é capaz de atualizar o timestamp do relógio lógico e recuperar as mensagens trocadas enquanto o usuário estivesse offline, desde que pelo menos um dos pares permanecesse ativo) e criptografia foram mantidas. Houve a implementação de um algoritmo de comunicação confiável (reliable muticast) baseado em Acknowledgement (Ack), um sistema para a verificação de pares ativos (online), a criação de um bot para envio de varias mensagens de maneira simultânea e implementação de uma funcionalidade que salva a lista de mensagens exibidas/pacotes em um arquivo do tipo txt.

Por fim, é de suma importância destacar a robustez e simplicidade do sistema desenvolvido, visto que cumpre com as principais exigências da startup contratante.

# 4. Conclusão
Durante a implementação desse sofware houve um contante desafio e esforço que contribuiram para o entendimento do funcionamento de sistemas distribuídos de maneira geral, além de possibilitar a compreensão do quão complexo e detalhista é a implementação de tais sistemas. É de suma importância para desenvolvedores entender aspectos inerentes a sincronização e os desafios e vantagens a cerca de algumas arquiteturas descentralizadas, especialmente a peer to peer e o modelo de comunicação confiável.

Todos os principais requisitos foram cumpridos de maneira eficiente, em especial a ordenação das mensagens e a garantia de que as listas de mensagens são as mesmas para todos os usuários ativos. É possível encerrar o software e recuperar mensagens trocadas anteriormente, desde que pelo menos um dos pares tenha ficado "online" e todos os pacotes que circulam na rede são criptografados.

Pensando em possíveis melhorias, é interessante que, posteriormente, o sistema de criptografia seja atualizado com a implementação de criptografia de chave pública-privada ou com outra forma mais segura porém igualmente eficaz. Também cogitou-se a busca por algoritmos mais complexos e robustos que solucionassem o problema, visto que a solução adotada tem como desvantagem o alto fluxo de pacotes na rede e uma possível sobrecarga do sistema a depender da quantidade de pares ativos e da quantidade de mensagens trocadas. Acredita-se que com essas simples melhorias a segurança do sistema como um todo melhore bastante junto à solidez e capacidade de envio e recebimento de mensagens.

# Referências
  * Python threading module: Disponível em: https://docs.python.org/3/library/threading.html. Acesso em: 20 de out. de 2023.
  * Algoritmos Distribuídos: Disponível em: https://www-di.inf.puc-rio.br/~endler/courses/DA/transp/D-Algos.PDF. Acesso em: 02 de fev. de 2024.
