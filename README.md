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
A placa conta com duas entradas USB conectadas a um controlador de HUB de duas portas e a um controlador USB (USB3300), conforme a imagem 1. O HUB USB funciona como um multiplicador de portas. Quando você conecta um hub USB a uma porta do computador, o hub em si se comunica com o controlador USB do computador para obter energia e informações sobre a porta.

![Imagem 1](https://github.com/caleosilva/Sistemas-Digitais-Problema-1/blob/main/readme_images/image1.png)


### 2.2 - Pacotes
Para que o sistema funcionasse de forma adequada, 6 tipos de pacotes foram estabelecidos:

1. **Pacote de mensagem**: { "message_type": "Message", "message_id": [ip_sender, current_timestamp], "text": ‘ ’, "ack_requested": Boolean }

   * message_type: string que identifica o tipo de pacote.
   * message_id: lista com o endereço IP do remetente da mensagem e o timestamp atual responsavel por identificar unicamente o pacote.
   * text: texto da mensagem que foi enviada. (Área de dados do pacote)
   * ack_requested: Booleano indicando se a mensagem precisa d confirmação.

2. **Solicitação de sincronização**: { "message_type": "Sync", "message_id": [ip_sender, current_timestamp] }

   * message_type: string que identifica o tipo de pacote.
   * message_id: lista com o endereço IP do remetente da mensagem e o timestamp atual responsavel por identificar unicamente o pacote.
   * text: texto informando que é uma solicitação de sincronização. (Área de dados do pacote)

3. **Verificação de pares ativos**: { "message_type": "Ping", "id": str(uuid.uuid4()) }

   * message_type: string que identifica o tipo de pacote.
   * message_id: Identificador Único Universal (uuid) que identifica unicamente esse tipo de pacote.
    
4. **Resposta a verificação de pares ativos**: { "message_type": "Pong", "id": message_data["id"] }
  
   * message_type: string que identifica o tipo de pacote.
   * message_id: Uuid igual ao id do pacote do tipo "Pong".

5. **Confirmação de recebimento de mensagem**: { "message_type": "Ack", "message_id": message_id }
   * message_type: string que identifica o tipo de pacote.
   * message_id: lista com o endereço IP do remetente da mensagem e o timestamp atual responsavel por identificar unicamente o pacote e igual ao da mensagem recebida.

6. **Confirmação de exibição de mensagem**:  { "message_type": "Confirmed", "message_id": message_id }
   * message_type: string que identifica o tipo de pacote.
   * message_id: lista com o endereço IP do remetente da mensagem e o timestamp atual responsavel por identificar unicamente o pacote e igual ao da mensagem enviada.
   

### 2.3 - Threads
A aplicação foi contruída com base na operação de cinco Threads distintas, além da Thread principal, cada uma desempenhando um papel específico ao longo de toda a execução do sistema:

1. **receive_messages**: Tem a função primordial de receber todos os pacotes que chegam, adicionando-os a uma fila para processamento posterior.
2. **order_packages**: Opera em paralelo, porém em conjunto com a Thread `receive_messages`, sendo responsável por tratar os pacotes da fila, garantindo que todos os pacotes sejam processados corretamente.
3. **send_all_ping**: Responsável por enviar a todos os pares da lista de pares o pacote de verificação de pares ativos (Ping) a cada meio segundo.
4. **check_status**: Opera em paralelo, porém em conjunto com a Thread `send_all_ping`, sendo responsável por verificar a cada 0.2 segundos quis foram os pares que responderam ao "Ping" e atualizar seus respectivos status.
5. **remove_pending_messages**:  Opera em paralelo, porém em conjunto com a Thread `order_packages` e com a funcionalidade de enviar mensagens. Assim, sendo responsável por verificar se todos os pares ativos confirmaram o recebimento das mensagens, enviar a confirmação de exibição de mensagens e mover as mensagens confirmadas para a lista de exibição.

### 2.4 - Criptografia
A estratégia criptografica adotada foi a de deslocamento de caracteres. Também conhecida como cifra de César, é uma técnica de criptografia clássica que opera deslocando cada caractere em uma mensagem por um número fixo de posições no alfabeto. Essa abordagem foi escolhida após a tentativa (sem sucesso) de implementação de criptografia utilizando chaves pública-privada.

Ao implementar criptografia utilizando chaves pública-privada é necessário garantir que a troca de chaves entre os pares ocorra de maneira eficiente, eficaz e segura. Ou seja, é necessário garantir que todos os pares conheçam as chaves públicas dos usuários conectados aos sistema no momento que a mensagem chega. Por esse motivo, optou-se por reenviar a chave pública para todos os pares antes de cada pacote ser enviado, o que ocasionou erros relacionados a sincronização da lista de chaves, aumento expressivo do número de pacotes circulando na rede e baixas no desempenho do sistema como um todo.

Ao implementar a cifra de César, o software ganhou em desempenho e simplicidade, entretanto o sistema ficou bastante vulnerável a ataques, especialmente por meio de métodos de força bruta, devido ao pequeno espaço de chaves possíveis. 

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
