select b.nome, ec.data,
sum(ce.valor * ce.qnt) as subtotal,
sum(ec.desconto) as desc,
round(sum(ce.valor * ce.qnt) - sum(ec.desconto)) as total,
sum(ec.pagtocliente) as pagamento,
round(sum(ec.pagtocliente) - (sum(ce.valor * ce.qnt) - sum(ec.desconto))) as troco
from executorcorte ec
join pessoa b on b.id = ec.id_barbeiro
join corteexec ce on ce.id_executor = ec.id
group by b.id;

//

select b.nome, ec.data,
sum(ce.valor * ce.qnt) as subtotal,
sum(ec.desconto) as desc,
round(sum(ce.valor * ce.qnt) - sum(ec.desconto)) as total,
sum(ec.pagtocliente) as pagamento,
round(sum(ec.pagtocliente) - (sum(ce.valor * ce.qnt) - sum(ec.desconto))) as troco
from executorcorte ec
join pessoa b on b.id = ec.id_barbeiro
join corteexec ce on ce.id_executor = ec.id
group by ce.id_executor, b.id;


//

select * from executorcorte;
select * from corteexec;
select sum(ec.pagtocliente), sum(ce.valor) from executorcorte ec join corteexec ce on ce.id_executor = ec.id group by ec.id_barbeiro;
select ec.pagtocliente, sum(ce.valor) from executorcorte ec join corteexec ce on ce.id_executor = ec.id group by ec.id;
select sum(pagamentos), sum(valores) from (select ec.pagtocliente as pagamentos, sum(ce.valor) as valores from executorcorte ec join corteexec ce on ce.id_executor = ec.id group by ec.id);
select barb, sum(pagto) as pagamento, sum(vlr) as valorcorte from (select ec.id_barbeiro as barb, ec.pagtocliente as pagto, sum(ce.valor) as vlr from executorcorte ec join corteexec ce on ce.id_executor = ec.id group by ec.id) group by barb;

//

select 
	idbarb, nome,
	sum(vlrcorte) as valorcorte,
	sum(desconto) as desconto,
	sum(total) as total,
	sum(pagtoclien) as pagamento,
	sum(troco) as troco
from (
	select ec.id_barbeiro as idbarb, b.nome as nome, ec.pagtocliente as pagtoclien, sum(ce.valor) as vlrcorte,
	ec.desconto as desconto, sum(ce.valor) - ec.desconto as total,
	ec.pagtocliente - (sum(ce.valor) - ec.desconto) as troco,
	ec.data as data
	from executorcorte ec
	join corteexec ce on ce.id_executor = ec.id
	join pessoa b on b.id = ec.id_barbeiro
	group by ec.id
)
group by idbarb;

//










select b.nome, c.nome, ce.valor, ce.qnt, ce.valor * ce.qnt as total from executorcorte ec join pessoa b on b.id = ec.id_barbeiro join corteexec ce on ce.id_executor = ec.id join corte c on c.id = ce.id_corte
where ec.data between '2024-01-01' and '2024-05-20';



insert into cortesexec (id_executor, id_corte, valor, qnt) values (1, 4, 25, 4), (2, 2, 10, 6);