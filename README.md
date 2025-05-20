# 42-cursus-philosophers

## Contexto

- Um ou mais filósofos sentam-se em uma mesa redonda.
- Há uma grande tigela de espaguete no meio da mesa.
- Os filósofos alternadamente comem, pensam ou dormem.
	- Enquanto comem, não pensam nem dormem;
	- enquanto pensam, não comem nem dormem; 
	- e, claro, enquanto dormem, não comem nem pensam.
- Também há garfos na mesa. Há tantos garfos quanto filósofos.
- Como servir e comer espaguete com apenas um garfo é muito inconveniente, um filósofo pega o garfo direito e o esquerdo para comer, um em cada mão.
- Quando um filósofo termina de comer, ele coloca os garfos de volta na mesa e começa a dormir. Uma vez acordado, ele começa a pensar novamente. A simulação para quando um filósofo morre de fome.
- Todo filósofo precisa comer e nunca deve passar fome.
- Filósofos não falam uns com os outros.
- Filósofos não sabem se outro filósofo está prestes a morrer.
- Não é preciso dizer que filósofos devem evitar morrer!

- Variáveis ​​globais são proibidas!
- O programa deve receber os seguintes argumentos:
	- `number_of_philosophers`: O número de filósofos e também o número de garfos.
	- `time_to_die` (em milissegundos): Se um filósofo não começou a comer em `X` milissegundos desde o início de sua última refeição ou do início da simulação, ele morre.
	- `time_to_eat` (em milissegundos): O tempo que um filósofo leva para comer. Durante esse tempo, ele precisará segurar dois garfos.
	- `time_to_sleep` (em milissegundos): O tempo que um filósofo passará dormindo.
	- `number_of_times_each_philosopher_must_eat` (argumento opcional): Se todos os filósofos tiverem comido pelo menos `X`	vezes, a simulação para. Se não for especificado, a simulação para quando um filósofo morre.
- Cada filósofo tem um número que varia de 1 a number_of_philosophers.
- O filósofo número 1 fica ao lado do filósofo número number_of_philosophers. Qualquer outro filósofo número N fica entre o filósofo número N - 1 e o filósofo número N + 1. Ou seja:
	- **Primeiro filósofo** (número 1):
		- Vizinho à esquerda: filósofo número number_of_philosophers (último filósofo).
		- Vizinho à direita: filósofo número 2.
	- **Último filósofo** (número number_of_philosophers):
		- Vizinho à esquerda: filósofo número number_of_philosophers - 1.
		- Vizinho à direita: filósofo número 1 (primeiro filósofo).
	- **Qualquer outro filósofo** (número N, onde 1 < N < number_of_philosophers):
		- Vizinho à esquerda: filósofo número N - 1.
		- Vizinho à direita: filósofo número N + 1.
- Sobre os logs do programa:
	- Qualquer mudança de estado de um filósofo deve ser formatada da forma a baixo, onde `timestamp_in_ms` é o tempo em milissegundos a partir do início da simulação, e `X` é o número do filósofo.
		- `timestamp_in_ms` X pegou um fork
		- `timestamp_in_ms` X está comendo
		- `timestamp_in_ms` X está dormindo
		- `timestamp_in_ms` X está pensando
		- `timestamp_in_ms` X morreu
	- Uma memutexnsagem de estado exibida não deve ser misturada com outra mensagem.
	- Uma mensagem anunciando a morte de um filósofo deve ser exibida no máximo 10 ms após a morte real do filósofo.
	- Novamente, filósofos devem evitar morrer!
	- Seu programa não deve ter nenhuma corrida de dados.

## Requisitos Técnicos

- Funções permitidas: `memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock`
- Cada filósofo deve ser um thread.
- Há um garfo entre cada par de filósofos. Portanto, se houver vários filósofos, cada filósofo tem um garfo no seu lado esquerdo e um garfo no seu lado direito. Se houver apenas um filósofo, deve haver apenas um garfo na mesa.
- Para evitar que os filósofos dupliquem forks (garfos), deve-se proteger o estado dos garfos com um `mutex` para cada um deles.

## Refinamentos

### Entendimento melhor sobre `precisará segurar dois garfos`

No problema dos filósofos, cada filósofo precisa segurar dois garfos para poder comer. Aqui está o que isso significa:

Garfos compartilhados: Os garfos estão posicionados entre os filósofos na mesa circular. Cada garfo é compartilhado por dois filósofos adjacentes.

Dois garfos para comer: Para que um filósofo possa comer, ele precisa segurar os dois garfos que estão ao seu lado. Isso significa que ele precisa pegar o garfo à sua esquerda e o garfo à sua direita.

Condição de espera: Se um dos garfos que o filósofo precisa já estiver sendo usado por outro filósofo, ele deve esperar até que o garfo esteja disponível.

Essa necessidade de segurar dois garfos cria uma situação de concorrência e pode levar a problemas como deadlock (onde todos os filósofos estão esperando indefinidamente) ou starvation (onde um filósofo nunca consegue pegar os dois garfos necessários para comer). O problema dos filósofos é um clássico exemplo de problemas de sincronização em sistemas concorrentes.

### Entendimento sobre `corrida de dados`

Corrida de dados é um problema que ocorre em sistemas concorrentes quando a saída do programa depende da ordem de execução das threads. Se a ordem de execução das threads for alterada, a saída do programa também será alterada. Isso pode levar a resultados inesperados e bugs difíceis de reproduzir.

Para evitar corridas de dados, é importante garantir que as threads não acessem ou modifiquem as mesmas variáveis ao mesmo tempo. Isso pode ser feito usando mecanismos de sincronização, como mutexes, semáforos ou variáveis de condição.

## Entendimento sobre `haver apenas um garfo na mesa`

Se houver apenas um filosofo deve haver apenas um garfo na mesa!

Porém, durante o tempo que o filoso estiver comendo ele precisará segurar dois garfos.

Não há uma contradição?

Não, pois o filosofo só precisa segurar dois garfos para comer, mas não significa que ele precisa segurar os dois garfos ao mesmo tempo. Ele pode pegar um garfo, comer, largar o garfo, pegar o outro garfo e comer novamente.

- Contexto de vários filósofos: 
	- **Vários filósofos**: Quando há vários filósofos, cada filósofo precisa pegar dois garfos para comer: um à sua esquerda e um à sua direita. Os garfos são compartilhados entre os filósofos adjacentes.
	- **Distribuição dos garfos**: Há um garfo entre cada par de filósofos. Portanto, se houver N filósofos, haverá N garfos, um entre cada par de filósofos.
- Caso especial de um único filósofo: 
	- **Um único filósofo**: Se houver apenas um filósofo, a situação muda. Não há outros filósofos com quem compartilhar os garfos.
	- **Necessidade de dois garfos**: Mesmo que o filósofo precise de dois garfos para comer, a regra de "apenas um garfo na mesa" simplifica a situação, pois não há concorrência ou necessidade de sincronização com outros filósofos.

## Entendimento sobre `filósofos devem evitar morrer`

No problema dos filósofos, os filósofos devem evitar morrer. Isso significa que eles devem seguir as regras do problema e evitar situações que possam levar à morte. Alguns exemplos de situações que podem levar à morte dos filósofos incluem:

- Um filósofo tentando pegar um garfo que já está sendo usado por outro filósofo.
- Um filósofo tentando comer sem segurar os dois garfos necessários.
- Um filósofo esperando indefinidamente por um garfo que nunca será liberado.

## Entendimento sobre `cada filósofo deve ser um thread`

No problema dos filósofos, cada filósofo deve ser representado por uma thread separada. Isso significa que cada filósofo terá seu próprio thread de execução, que será responsável por realizar as ações do filósofo, como pensar, comer e dormir.

Usar threads para representar os filósofos permite que eles executem suas ações de forma concorrente e paralela, o que é essencial para resolver o problema dos filósofos de forma eficiente. Cada thread de filósofo terá seu próprio contexto de execução e poderá interagir com os outros filósofos por meio de mecanismos de sincronização, como mutexes e semáforos.

## Entendimento sobre `garfo entre cada par de filósofos`

No problema dos filósofos, os garfos são posicionados entre cada par de filósofos na mesa circular. Isso significa que cada filósofo terá um garfo à sua esquerda e um garfo à sua direita, que serão compartilhados com os filósofos adjacentes.

A presença de um garfo entre cada par de filósofos é importante para garantir que os filósofos possam pegar os garfos necessários para comer. Se não houver garfos suficientes na mesa, os filósofos não poderão comer e a simulação falhará.

Para evitar problemas como deadlock e starvation, é importante garantir que os garfos sejam compartilhados corretamente entre os filósofos e que eles sigam as regras do problema ao pegar e liberar os garfos.

## Entendimento sobre `proteger o estado dos garfos com um mutex`

No problema dos filósofos, é importante proteger o estado dos garfos com um mutex para evitar condições de corrida e garantir a consistência dos dados. Isso significa que cada garfo terá seu próprio mutex associado, que será usado para controlar o acesso aos garfos pelos filósofos.

Quando um filósofo deseja pegar um garfo, ele deve primeiro adquirir o mutex associado ao garfo para garantir que nenhum outro filósofo esteja usando o garfo ao mesmo tempo. Depois de pegar o garfo, o filósofo pode usá-lo para comer e, em seguida, liberá-lo, liberando o mutex associado ao garfo.

Usar mutexes para proteger o estado dos garfos é uma prática comum em programação concorrente e é essencial para evitar problemas como deadlock, starvation e corridas de dados. Garantir que os filósofos sigam as regras do problema e usem os mutexes corretamente é fundamental para resolver o problema dos filósofos de forma eficiente e correta.

## Referências