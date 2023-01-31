--Ex3
create sequence exp_sequencia; -- Cria sequencia exp_sequencia que começa a 1 e incrementa por 1
select exp_sequencia.currval from dual; -- Erro, pois a sequencia nao foi inicializada
select exp_sequencia.nextval from dual; -- Inicializa a sequencia e devolve o valor atual (1)
select exp_sequencia.nextval from dual;  -- Incrementa a sequencia e devolve o valor atual (2)
select exp_sequencia.nextval from dual;  -- Incrementa a sequencia e devolve o valor atual (3)
select exp_sequencia.currval from dual; -- Devolve o valor atual da sequencia
drop sequence exp_sequencia; -- Destroi a sequencia exp_sequencia

--Ex4
DROP TABLE EDITORAS_BACKUP;
CREATE TABLE EDITORAS_BACKUP AS (SELECT * FROM EDITORAS);
ALTER TABLE EDITORAS_BACKUP ADD (
  CONSTRAINT PK_ID_EDITORA_BK PRIMARY KEY (CODIGO_EDITORA),
  CONSTRAINT UK_N_CONTRIB_BK UNIQUE (N_CONTRIBUINTE));
  

--Ex5
CREATE SEQUENCE SEQ_EDITBACK
  START WITH 4
  INCREMENT BY 1
  NOCYCLE
  NOMAXVALUE;
  

--Ex6
ALTER TABLE EDITORAS_BACKUP MODIFY (MORADA VARCHAR(60));
INSERT INTO EDITORAS_BACKUP VALUES (seq_editback.nextval, 'D.Quixote', 901111111, 'Rua Cidade de Córdova, n.2 2610-038 Alfragide', 707252252, 707252253);
INSERT INTO EDITORAS_BACKUP VALUES (seq_editback.nextval, 'Almedina', 901212121, 'Rua Fernandes Tomás, n.º 76 a 80, 3000-167 Coimbra', 239851903, 239851904);


--Ex7
select seq_editback.currval from dual;
select seq_editback.nextval from dual;
select seq_editback.currval from dual;


--Ex8
DROP SEQUENCE seq_editback;

--Ex9
CREATE VIEW LIVROS_INFORMATICA AS
SELECT * FROM LIVROS
WHERE upper(genero) = 'INFORMÁTICA';


--Ex10
insert into livros_informatica (codigo_livro, titulo,isbn, genero) values (30,'Uma noite de Verão', 8000000001,'Informática');
insert into livros_informatica (codigo_livro, titulo,isbn, genero) values (31,'O céu é azul',8000000002,'Romance');
insert into livros (codigo_livro, codigo_editora, codigo_autor,titulo,isbn, genero) values (32,2, 2,'Longe de tudo',8000000003,'Informática');


--Ex11
DELETE FROM LIVROS
WHERE CODIGO_LIVRO IN (30, 31, 32);


--Ex12
DROP VIEW LIVROS_INFORMATICA;

--Ex13
DROP TABLE LIVROS_BACKUP;
CREATE TABLE LIVROS_BACKUP AS (SELECT * FROM LIVROS);


--Ex14
CREATE VIEW AUTOR_LIVRO AS
SELECT AU.NOME, L.TITULO
FROM AUTORES AU, LIVROS_BACKUP L
WHERE AU.CODIGO_AUTOR = L.CODIGO_AUTOR;


--Ex15
SELECT * FROM AUTOR_LIVRO;
DELETE LIVROS_BACKUP;
SELECT * FROM AUTOR_LIVRO; 
--Não é possível vizualizar nada, pois a vista não guarda informação e apagamos os registos na tabela original


--Ex16
DROP TABLE LIVROS_BACKUP;
SELECT * FROM AUTOR_LIVRO; 
-- ERRO, pois a View está a tentar aceder a uma tabela que não existe


--Ex17
CREATE VIEW LIVROS_VENDIDOS AS
SELECT L.TITULO, AU.NOME, SUM(V.QUANTIDADE) AS QUANT_VEND
FROM LIVROS L, VENDAS V, AUTORES AU
WHERE L.CODIGO_LIVRO = V.CODIGO_LIVRO
AND L.CODIGO_AUTOR = AU.CODIGO_AUTOR
GROUP BY V.CODIGO_LIVRO, L.TITULO, AU.NOME
ORDER BY 3 DESC;


--Ex18
SELECT * FROM USER_TABLES;


--Ex19
SELECT * FROM USER_CONSTRAINTS;