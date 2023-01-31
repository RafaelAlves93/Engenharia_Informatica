--Ex3
CREATE TABLE autores2 (
  CODIGO_AUTOR	  NUMBER(4,0) CONSTRAINT pk_autores2 PRIMARY KEY,
  NOME	  VARCHAR2(30 BYTE) CONSTRAINT ck_nome_notnull NOT NULL CONSTRAINT ck_nome_maiuscula CHECK(nome = upper(nome)),
  N_CONTRIBUINTE	  NUMBER(9,0) CONSTRAINT nn_nif NOT NULL CONSTRAINT uk_nif UNIQUE,
  MORADA	  VARCHAR2(50 BYTE),
  IDADE 	NUMBER(4,0) CONSTRAINT ck_idade_menor_200 CHECK(idade BETWEEN 0 and 200),
  SEXO	  CHAR(1 BYTE) CONSTRAINT ck_sexo_m_f CHECK(sexo in ('F', 'M')),
  NACIONALIDADE	  VARCHAR2(20 BYTE),
  GENERO_PREFERIDO	  VARCHAR2(20 BYTE)
);


--Ex4
CREATE TABLE avaliacoes (
  CODIGO_LIVRO    NUMBER(4,0) CONSTRAINT fk_codigo_livro REFERENCES LIVROS(CODIGO_LIVRO),
  CODIGO_CLIENTE    NUMBER(4,0) CONSTRAINT fk_codigo_cliente REFERENCES CLIENTES(CODIGO_CLIENTE),
  NOTA    NUMBER(1) CONSTRAINT ck_nota_1a3 CHECK(nota between 1 and 5),
  CONSTRAINT pk_avaliacoes PRIMARY KEY(CODIGO_LIVRO, CODIGO_CLIENTE)
);


--Ex5
DROP TABLE livros_backup;
CREATE TABLE livros_backup AS (
  SELECT CODIGO_LIVRO,
         CODIGO_EDITORA,
         CODIGO_AUTOR,
         TITULO,
         ISBN,
         upper(GENERO) as GENERO,
         PRECO_TABELA,
         PAGINAS,
         QUANT_EM_STOCK,
         UNIDADES_VENDIDAS,
         DATA_EDICAO
  FROM LIVROS 
);


--Ex6
ALTER TABLE LIVROS_BACKUP ADD (
  CONSTRAINT PK_LIVROS_BK PRIMARY KEY(CODIGO_LIVRO),
  CONSTRAINT FK_LIVROS_BK_COD_ED_EDITORAS FOREIGN KEY(CODIGO_EDITORA) REFERENCES EDITORAS(CODIGO_EDITORA),
  CONSTRAINT FK_LIVROS_BK_COD_AU_AUTORES FOREIGN KEY(CODIGO_AUTOR) REFERENCES AUTORES(CODIGO_AUTOR)
);


--Ex7
INSERT INTO LIVROS_BACKUP VALUES (
  51,
  (SELECT CODIGO_EDITORA FROM EDITORAS WHERE UPPER(NOME) = 'FCA - EDITORA'),
  (SELECT CODIGO_AUTOR FROM AUTORES WHERE INITCAP(NOME) = 'Sérgio Sousa'),
  'Informática para todos', 132424, 'Informática', 24, 430, NULL, 0, SYSDATE
);


--Ex8
INSERT INTO autores2 (CODIGO_AUTOR, NOME, N_CONTRIBUINTE)
  values (45, 'JOSÉ MAGALHÃES', 77665544);


--Ex9
DELETE FROM livros_backup WHERE CODIGO_LIVRO = 51;


--Ex10
UPDATE livros_backup 
SET PRECO_TABELA = PRECO_TABELA * 1.1 --, se quiser mais alterações separo por virgula
WHERE GENERO = 'AVENTURA';


--Ex11
DELETE FROM LIVROS_BACKUP WHERE PRECO_TABELA < (SELECT AVG(PRECO_TABELA) FROM LIVROS_BACKUP WHERE GENERO = 'INFORMÁTICA');


--Ex12
DROP TABLE AUTORES_BACKUP;
CREATE TABLE AUTORES_BACKUP AS (SELECT * FROM AUTORES);


--Ex13
ALTER TABLE AUTORES_BACKUP ADD (NLIVROS   NUMBER(3,0) DEFAULT 0 CONSTRAINT CK_NLIVROS_0_150 CHECK(NLIVROS BETWEEN 0 AND 150));


--Ex14
UPDATE AUTORES_BACKUP AB
SET NLIVROS = NVL((SELECT COUNT(CODIGO_LIVRO) CNT
                   FROM LIVROS
                   WHERE CODIGO_AUTOR = AB.CODIGO_AUTOR
                   GROUP BY CODIGO_AUTOR), 0);


--Ex15
UPDATE AUTORES_BACKUP AB SET GENERO_PREFERIDO = (SELECT L.GENERO -- Ir aos livros agrupados por autor e genero. Contar os livros. Manter apenas as linhas onde o numero de livros nesse grupo é igual ao maximo de livros
                                                 FROM LIVROS L
                                                 WHERE L.CODIGO_AUTOR = AB.CODIGO_AUTOR
                                                 AND ROWNUM = 1 -- Manter apenas uma linha de output (quando o autor escrever igual quantidade máxima de dois ou mais generos)
                                                 GROUP BY L.CODIGO_AUTOR, L.GENERO
                                                 HAVING COUNT(L.CODIGO_LIVRO) = (SELECT MAX(COUNT(LL.CODIGO_LIVRO)) -- Escolher o numero maximo de livros dentro de cada genero de cada autor
                                                                                 FROM LIVROS LL
                                                                                 WHERE L.CODIGO_AUTOR = LL.CODIGO_AUTOR -- restringindo ao autor atual
                                                                                 GROUP BY LL.CODIGO_AUTOR, LL.GENERO));


--Ex16
CREATE TABLE EDITORAS_BACKUP AS (SELECT * FROM EDITORAS);


--Ex17
DROP TABLE EDITORAS_BACKUP;


--Ex18
ALTER TABLE LIVROS_BACKUP ADD (EDICAO   NUMBER(7));


--Ex19
UPDATE LIVROS_BACKUP LB SET UNIDADES_VENDIDAS = NVL((SELECT SUM(V.QUANTIDADE)
                                                     FROM VENDAS V
                                                     WHERE V.CODIGO_LIVRO = LB.CODIGO_LIVRO),0);


--Ex20
UPDATE VENDAS_BACKUP VB SET TOTAL_VENDA = (SELECT V.QUANTIDADE * V.PRECO_UNITARIO
                                           FROM VENDAS V
                                           WHERE VB.CODIGO_VENDA = V.CODIGO_VENDA);


--Ex21
CREATE TABLE VENDAS_BACKUP AS (SELECT * FROM VENDAS);


--Ex22
DELETE FROM VENDAS_BACKUP VB WHERE TO_CHAR(DATA_VENDA, 'DD-MON-YYYY') LIKE '%-JAN-%'; 


--Ex23
DELETE FROM VENDAS_BACKUP WHERE CODIGO_LIVRO = (SELECT CODIGO_LIVRO
                                                FROM LIVROS, (SELECT AUTORES.CODIGO_AUTOR CA, MAX(PRECO_TABELA) MPT
                                                              FROM LIVROS, AUTORES
                                                              WHERE LIVROS.CODIGO_AUTOR = AUTORES.CODIGO_AUTOR
                                                              AND NOME = 'Sérgio Sousa'
                                                              GROUP BY AUTORES.CODIGO_AUTOR) MC
                                                WHERE CODIGO_AUTOR = MC.CA
                                                AND PRECO_TABELA = MC.MPT);