

drop schema if exists progettobasi cascade; 

CREATE SCHEMA progettobasi;

set search_path to progettobasi;

create table macrozona(
nome varchar(30) primary key
);

create table contiene(
nome_macrozona varchar(30),
nome_regione varchar(30),	
constraint pk_contiene primary key(nome_macrozona,nome_regione )
);

create table regione(
nome varchar(30) primary key,
n_comuni integer not null,	
n_residenti integer not null,
check (n_comuni > 0 ),
check (n_residenti > 0)	
);

create table cliente (
p_iva integer primary key,
nome varchar(30) ,
sede varchar(30),
email varchar(30), 
cod_macrozona varchar(30),
cod_regione varchar(30)	
);



create table segue(
clienteid integer,
agenteid character(15),
CONSTRAINT pk_segue PRIMARY KEY (clienteid,agenteid)	
);

create table agente(
cf character(15) primary key,
nome varchar(30) not null,
email varchar(30),
sesso char not null,
capo_area character(15)	
);

create domain pagamento as varchar(30)
check (value in ('paypal','visa','mastercard','bonifico'));

create table ordine(
n_ordine integer ,
costo_ordine real not null,
data_ordine varchar(30) not null,
metodo_pagamento pagamento,
cod_cliente integer not null,	
primary key(n_ordine),
check( n_ordine > 0)	
);


create table fornitore (
P_IVA character(11) primary key,
telefono numeric(9,0) not null,
email varchar(30) not null,
nome varchar(30) not null,
sede varchar(30) not null	
);


create domain qualità_carne as varchar(30)
check (value in ('prima scelta','seconda scelta', 'terza scelta'));


create table partita(
cod_part numeric(10,0) primary key,
peso real not null,	
n_prodotti integer not null,
costo_spedizione real not null,	
costo_stoccaggio real not null,
costo_acquisto real not null,	
P_IVAForn character(11)	not null,
scelta	qualità_carne not null,
check (n_prodotti > 0), 
check (costo_spedizione > 0),
check (costo_stoccaggio > 0),
check (peso > 0 ),
check (costo_acquisto > 0)	
);


create domain tipologia_carne as varchar(30)
check (value in ('coscia pollo','fiorentina','costata','salsiccia','cotoletta'));

create table articolo(
cod_art numeric(10,0) ,
data_scadenza date not null,
prezzo real not null,
peso real not null,
cod_part numeric(10,0),
tipocarne	tipologia_carne,
ordine integer,
constraint pk_articolo primary key(cod_art,cod_part)	
);

create table linea(
tipocarne tipologia_carne primary key
);



alter table agente
add constraint fk_agente
foreign key(capo_area) references agente(cf)
on delete cascade on update cascade; 

alter table segue
add constraint fk_segue
foreign key(clienteid) references cliente(P_IVA)
on delete cascade on update cascade; 

alter table segue
add constraint fk_segue1
foreign key(agenteid) references agente(cf)
on delete cascade on update cascade; 


alter table cliente
add constraint fk_cliente
foreign key(cod_macrozona) references macrozona(nome)
on delete cascade on update cascade; 

alter table cliente
add constraint fk_cliente1
foreign key(cod_regione) references regione(nome)
on delete cascade on update cascade; 


alter table contiene 
add constraint fk_contiene
foreign key(nome_macrozona) references macrozona(nome)
on delete cascade on update cascade;

alter table contiene
add constraint fk_contiene1
foreign key(nome_regione) references regione(nome)
on delete cascade on update cascade; 


alter table ordine
add constraint fk_ordine
foreign key(cod_cliente) references cliente(P_IVA)
on delete cascade on update cascade; 



alter table partita
add constraint fk_partita
foreign key(P_IVAForn) references fornitore(P_IVA)
on delete cascade on update cascade;


alter table articolo
add constraint fk_articolo
foreign key(cod_part) references partita(cod_part)
on delete cascade on update cascade; 

alter table articolo 
add constraint fk_articolo2
foreign key(tipocarne) references linea(tipocarne)
on delete cascade on update cascade;


alter table articolo 
add constraint fk_articolo3
foreign key(ordine) references ordine(n_ordine)
on delete cascade on update cascade;


