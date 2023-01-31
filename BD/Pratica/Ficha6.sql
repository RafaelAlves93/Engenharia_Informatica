--Ex3
select nome
from autores
minus
select nome
from autores,livros
where autores.codigo_autor=livros.codigo_autor 
and to_char(data_edicao,'YYYY')<> to_char(sysdate,'YYYY')
and codigo_livro like '%';

--Ex4
select nome, to_char(count(titulo)) as "Num.Livros"
from livros l,autores a 
where l.codigo_autor=a.codigo_autor
group by nome
union( 
	select nome, 'nenhum'
	from autores
	minus
	select nome, 'nenhum'
	from autores a, livros l
	where a.codigo_autor=l.codigo_autor
)order by 1; /*nome*/