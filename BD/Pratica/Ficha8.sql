--Ex3
select titulo,preco_tabela as "PRECO_TABELA"
from livros
where upper (genero) = 'INFORMÁTICA' and preco_tabela = (select
max(preco_tabela)
from livros
where upper(genero)='INFORMÁTICA');


--Ex4
select titulo, preco_tabela as "PRECO_TABELA"
from livros
where upper (genero) = 'INFORMÁTICA' and preco_tabela >= all (select
max(preco_tabela)
from livros
where upper (genero) = 'INFORMÁTICA');


--Ex5
select titulo, preco_tabela as "PRECO_TABELA"
from livros l
where upper (genero) = 'INFORMÁTICA' and not exists (select preco_tabela
from livros
where upper (genero) = 'INFORMÁTICA' and livros.preco_tabela > l.preco_tabela);


--Ex6
select titulo, preco_tabela as "PRECO_TABELA"
from livros l, (select max(preco_tabela) maximo
from livros
where upper (genero) ='INFORMÁTICA') m
where upper (genero) = 'INFORMÁTICA' and preco_tabela = m.maximo;


--Ex7
select distinct nome as "NOME"
from autores a , livros l,(select avg(livros.paginas) media
from livros, autores
where livros.codigo_autor = autores.codigo_autor) m
where l.codigo_autor = a.codigo_autor and l.paginas > m.media
order by a.nome;

--Ex8
select distinct A.NOME
from AUTORES A, LIVROS L
where A.CODIGO_AUTOR = L.CODIGO_AUTOR
group by a.nome
having count(L.TITULO) > (select avg(count(*))
from livros
group by codigo_autor);

--Ex9
select livros.genero, titulo, unidades_vendidas
from livros,(select genero, max(unidades_vendidas) MaisVendido
from livros
group by genero) a
where livros.UNIDADES_VENDIDAS = a.MaisVendido
and livros.genero = a.genero
order by 1;

--Ex10

