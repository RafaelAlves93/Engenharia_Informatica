--Ex3
select autores.codigo_autor,autores.nome,titulo,preco_tabela,editoras.codigo_editora
from autores inner join livros on (autores.codigo_autor=livros.codigo_autor)
inner join editoras on (livros.codigo_editora=editoras.codigo_editora)
where editoras.nome= 'FCA - EDITORA'
and preco_tabela= (select max(preco_tabela)
from livros inner join editoras on (livros.codigo_editora=editoras.codigo_editora)
where editoras.nome='FCA - EDITORA');


--Ex4
select aut.nome, liv.titulo, cl.mpl as "LIVROS FCA", count(liv.codigo_livro) as "Total de Livros"
from autores aut, editoras edi, livros liv, (select codigo_autor as mplca, count(codigo_livro) as mpl
                                             from livros, editoras
                                             where livros.codigo_editora = editoras.codigo_editora
                                             and livros.preco_tabela = (select max(preco_tabela) 
                                                                        from livros, editoras
                                                                        where livros.codigo_editora = editoras.codigo_editora
                                                                        and upper(editoras.nome) like '%FCA%')
                                             and upper(editoras.nome) like '%FCA%'
                                             group by codigo_autor) cl
where aut.codigo_autor = liv.codigo_autor
and liv.codigo_editora = edi.codigo_editora
and liv.codigo_autor = cl.mplca
and upper(edi.nome) like '%FCA%'
group by aut.nome, liv.titulo, cl.mpl;


--Ex5
select aut.nome, NVL(ct.ctl, 0) as "Genero Preferido", count(l.codigo_livro) as "Total de Livros"
from livros l, autores aut, (select aut.codigo_autor as ca, count(codigo_livro) as ctl
                             from livros l, autores aut
                             where l.codigo_autor = aut.codigo_autor (+)
                             and upper(l.genero) = upper(aut.genero_preferido)
                             group by aut.codigo_autor) ct
where l.codigo_autor (+) = aut.codigo_autor
and aut.codigo_autor = ct.ca (+)
group by aut.nome, ct.ctl
order by 1;

--Ex6
select editoras.codigo_editora,editoras.nome,totlivros."cont" as "NLIVROS"
from editoras inner join livros on(livros.codigo_editora=editoras.codigo_editora)
inner join
(select count(titulo) as "cont",editoras.codigo_editora as "cod"
from editoras inner join livros on (editoras.codigo_editora=livros.codigo_editora)
group by editoras.codigo_editora) totlivros
on(totlivros."cod"=editoras.codigo_editora)

group by editoras.codigo_editora,editoras.nome,totlivros."cont"
having (sum(unidades_vendidas)=(
(select max(sum(unidades_vendidas))
from editoras inner join livros on(livros.codigo_editora=editoras.codigo_editora)
group by editoras.codigo_editora)));


--Ex7
select 'O autor ' || aut.nome || ' escreveu ' || b.num_edit || ' de ' || count(livros.codigo_livro) || ' livros para a editora ' || b.ned || '.' as Resultado
from autores aut, livros,
                  (select codigo_autor as ca, e.nome as ned, count(codigo_livro) as num_edit
                   from livros l, editoras e, (select editoras.codigo_editora as ce, max(unidades_vendidas)
                                               from editoras, vendas, livros
                                               where editoras.codigo_editora = livros.codigo_editora
                                               and vendas.codigo_livro = livros.codigo_livro
                                               group by editoras.codigo_editora) d
                   where l.codigo_editora = e.codigo_editora
                   and e.codigo_editora = d.ce
                   group by codigo_autor, e.nome) b
where aut.codigo_autor = b.ca
and aut.codigo_autor = livros.codigo_autor
group by aut.nome, b.num_edit, b.ned
order by aut.nome;


--Ex8
select distinct cl.nome
from clientes cl, vendas v, (select codigo_livro as cliv
                             from livros
                             where preco_tabela = (select min(preco_tabela)
                                                   from livros
                                                   where upper(genero) like '%INFORMÁTICA%')) b
where cl.codigo_cliente = v.codigo_cliente
and v.codigo_livro = b.cliv; 
