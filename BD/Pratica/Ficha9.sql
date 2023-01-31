--Ex3
select titulo,preco_tabela as "PRECO", preco_medio, (preco_tabela - preco_medio) as "DIFERENÇA"
from livros l, (select codigo_autor, round(avg(preco_tabela),1) PRECO_MEDIO
from livros l
where GENERO = 'Informática'
group by codigo_autor) t
where lower(genero) = 'informática'
and l.codigo_autor = t.codigo_autor
order by 1;

--Ex4


--Ex5
select titulo, to_char(round(unidades_vendidas / s.sum_uv * 100, 1), '990.99') as percent
from livros, editoras, (select sum(unidades_vendidas) as sum_uv 
                        from livros, editoras
                        where livros.codigo_editora = editoras.codigo_editora
                        and nome like '%FCA%') s
where livros.codigo_editora = editoras.codigo_editora
and upper(nome) like '%FCA%'
order by 2 desc, 1;

--Ex6
select titulo
from livros, vendas, clientes
where livros.codigo_livro = vendas.codigo_livro
and vendas.codigo_cliente = clientes.codigo_cliente
and upper(morada) like '%LISBOA'
group by titulo
having sum(quantidade) = (select max(sum(quantidade))
                          from livros, vendas, clientes
                          where livros.codigo_livro = vendas.codigo_livro
                          and vendas.codigo_cliente = clientes.codigo_cliente
                          and upper(morada) like '%LISBOA'
                          group by livros.codigo_livro);

--Ex7
select aa.tl as "Total de Livros", ab.ta as "Total de Autores", ac.te as "Total de Editoras"
from (select count(codigo_livro) as tl from livros) aa,
     (select count(codigo_autor) as ta from autores) ab,
     (select count(codigo_editora) as te from editoras) ac;

--Ex8
select 'O autor ' || aut.nome || ' escreveu ' || count(livros.codigo_livro) || ' e ' || b.num_edit || ' sob a alçada da editora FCA - EDITORA' as "Resultado"
from autores aut, livros, (select codigo_autor, count(codigo_livro) as num_edit
						   from livros l, editoras e
                           where l.codigo_editora = e.codigo_editora
                           and e.nome like '%FCA%'
                           group by codigo_autor) b
where aut.codigo_autor = b.codigo_autor
and aut.codigo_autor = livros.codigo_autor
group by aut.nome, b.num_edit
order by aut.nome;