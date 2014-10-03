Mini projeto de arduino para a aula de sistemas reativos.

O projeto consiste em três componentes ligados ao arduino: Um led, um display de 7 segmentos
e um botão. O projeto é um jogo onde o usuário deve apertar o botão na hora certa para não perder
o jogo (o projeto é reativo pois a qualquer momento que o jogador apertar o botão errado o jogo
é interrompido no mesmo instante).

São exibidos diversos números aleatórios do display de 7 segmentos, num intervalo de 1 segundo.
Um número específico é escolhio como principal. Toda vez que este número principal aparecer o LED
acende e o jogador deve pressionar o botão antes de o display passar para o proximo numero. Depois de
três acertos, o número principal continua o mesmo, mas o LED não acende mais, então o jogador deve seguir apertando o botão mesmo sem a ajuda do LED. Depois de um determinado número de acertos, novos números são
sorteados para a sequência e para o número principal, e o intervalo de tempo entre a mudança dos números
diminui.

Caso o jogador não pressione o botão no número principal ou aperte o botão em um número diferente, ele perde o jogo.