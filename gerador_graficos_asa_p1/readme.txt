/****    INSTRUÇÕES   ****/

1. Extrai o conteudo do zip para uma pasta onde quiseres
2. Certifica-te que, para a pasta onde extraires o .zip, tens lá o teu projecto compilado e pronto para executar
3. Executa o comando ./generate_tests.sh (pode demorar)
4. Depois, executa ./test.sh ./<nome do executavel do teu projecto> |tee <nomequequiseres>.data
5. Em seguida, vais precisar de usar o gnuplot. Para fazeres download, caso nao tenhas, executa sudo apt-get install gnuplot-x11
6. Agora, executa gnuplot e quando o programa abrir, executa plot "<nomedoficheiro>.data"
7. Podes guardar a imagem que vai aparecer como .png ou .pdf
8. Para saires do gnuplot, faz quit


/****    ALGUMAS NOTAS    ****/

1. Os vertices sao gerados de 1000 em 1000 e vao ate 100000. Podem alterar isto no ciclo for.
2. Todo o processo de geração de testes pode demorar... sejam pacientes.
3. Confirmem que os testes estão correctos com o nome do ficheiro. :)
4. Para ordenarem os resultados: sort -n +0 -1 <nomedoficheiro>.data> <novoficheiro>.data
