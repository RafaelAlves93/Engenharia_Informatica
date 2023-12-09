/*==============================================================*/
/* DBMS name:      ORACLE Version 10g                           */
/* Created on:     1/16/2022 6:17:01 PM                         */
/*==============================================================*/


alter table ENTRADA
   drop constraint FK_ENTRADA_CONTEM_PRODUTO;

alter table ENTRADA
   drop constraint FK_ENTRADA_CONTROLAD_FUNCIONA;

alter table ENTRADA
   drop constraint FK_ENTRADA_FORNECIDA_FORNECED;

alter table GERIDA
   drop constraint FK_GERIDA_GERIDA_SECCOES;

alter table GERIDA
   drop constraint FK_GERIDA_GERIDA2_FUNCIONA;

alter table PRODUTO
   drop constraint FK_PRODUTO_PERTENCEM_SECCOES;

alter table VENDAS
   drop constraint FK_VENDAS_INCLUI_PRODUTO;

alter table VENDAS
   drop constraint FK_VENDAS_TEM_CLIENTE;

drop index CONTEM_FK;

drop index CONTROLADA_FK;

drop index FORNECIDA_FK;

drop index GERIDA2_FK;

drop index GERIDA_FK;

drop index PERTENCEM_FK;

drop index INCLUI_FK;

drop index TEM_FK;

drop table CLIENTE cascade constraints;

drop table ENTRADA cascade constraints;

drop table FORNECEDOR cascade constraints;

drop table FUNCIONARIO cascade constraints;

drop table GERIDA cascade constraints;

drop table PRODUTO cascade constraints;

drop table SECCOES cascade constraints;

drop table VENDAS cascade constraints;

/*==============================================================*/
/* Table: CLIENTE                                               */
/*==============================================================*/
create table CLIENTE  (
   COD_CLIENTE          NUMBER(6)                       not null,
   MORADA               VARCHAR2(50)                    not null,
   TELEFONE             NUMBER(9)                       not null,
   NOME_CLIENTE         VARCHAR2(30)                    not null,
   constraint PK_CLIENTE primary key (COD_CLIENTE)
);

/*==============================================================*/
/* Table: ENTRADA                                               */
/*==============================================================*/
create table ENTRADA  (
   COD_ENTRADA          NUMBER                          not null,
   NOME_FUNCIONARIO     VARCHAR2(30),
   COD_PRODUTO          NUMBER(6)                       not null,
   COD_FORNECEDOR       NUMBER                          not null,
   QUANTIDADE           NUMBER,
   constraint PK_ENTRADA primary key (COD_ENTRADA)
);

/*==============================================================*/
/* Index: CONTEM_FK                                             */
/*==============================================================*/
create index CONTEM_FK on ENTRADA (
   COD_PRODUTO ASC
);

/*==============================================================*/
/* Index: CONTROLADA_FK                                         */
/*==============================================================*/
create index CONTROLADA_FK on ENTRADA (
   NOME_FUNCIONARIO ASC
);

/*==============================================================*/
/* Index: FORNECIDA_FK                                          */
/*==============================================================*/
create index FORNECIDA_FK on ENTRADA (
   COD_FORNECEDOR ASC
);

/*==============================================================*/
/* Table: FORNECEDOR                                            */
/*==============================================================*/
create table FORNECEDOR  (
   COD_FORNECEDOR       NUMBER                          not null,
   NOME_FORN            VARCHAR2(30)                    not null,
   TELEFONE_FORN        VARCHAR2(9)                     not null,
   CONTIBUINTE          NUMBER(9)                       not null,
   constraint PK_FORNECEDOR primary key (COD_FORNECEDOR)
);

/*==============================================================*/
/* Table: FUNCIONARIO                                           */
/*==============================================================*/
create table FUNCIONARIO  (
   NOME_FUNCIONARIO     VARCHAR2(30)                    not null,
   IDADE                NUMBER                          not null,
   MORADA_FUNC          VARCHAR2(50)                    not null,
   TELEFONE_FUNC        NUMBER(9)                       not null,
   NUM_CONTRIBUINTE     NUMBER(9)                       not null,
   constraint PK_FUNCIONARIO primary key (NOME_FUNCIONARIO)
);

/*==============================================================*/
/* Table: GERIDA                                                */
/*==============================================================*/
create table GERIDA  (
   COD_SECCAO           NUMBER                          not null,
   NOME_FUNCIONARIO     VARCHAR2(30)                    not null,
   constraint PK_GERIDA primary key (COD_SECCAO, NOME_FUNCIONARIO)
);

/*==============================================================*/
/* Index: GERIDA_FK                                             */
/*==============================================================*/
create index GERIDA_FK on GERIDA (
   COD_SECCAO ASC
);

/*==============================================================*/
/* Index: GERIDA2_FK                                            */
/*==============================================================*/
create index GERIDA2_FK on GERIDA (
   NOME_FUNCIONARIO ASC
);

/*==============================================================*/
/* Table: PRODUTO                                               */
/*==============================================================*/
create table PRODUTO  (
   COD_PRODUTO          NUMBER(6)                       not null,
   COD_SECCAO           NUMBER                          not null,
   QUANT_STOCK          NUMBER                          not null,
   PRECO_TABELA         NUMBER(8,2)                     not null,
   NOME                 VARCHAR2(30)                    not null,
   constraint PK_PRODUTO primary key (COD_PRODUTO)
);

/*==============================================================*/
/* Index: PERTENCEM_FK                                          */
/*==============================================================*/
create index PERTENCEM_FK on PRODUTO (
   COD_SECCAO ASC
);

/*==============================================================*/
/* Table: SECCOES                                               */
/*==============================================================*/
create table SECCOES  (
   COD_SECCAO           NUMBER                          not null,
   SECCAO               VARCHAR2(10)                    not null,
   constraint PK_SECCOES primary key (COD_SECCAO)
);

/*==============================================================*/
/* Table: VENDAS                                                */
/*==============================================================*/
create table VENDAS  (
   COD_VENDA            NUMBER(6)                       not null,
   COD_PRODUTO          NUMBER(6),
   COD_CLIENTE          NUMBER(6)                       not null,
   PRECO_UNITARIO       NUMBER(8,2)                     not null,
   DATA_VENDA           DATE                            not null,
   QUANTIDADE_VENDIDA   NUMBER                          not null,
   constraint PK_VENDAS primary key (COD_VENDA)
);

/*==============================================================*/
/* Index: TEM_FK                                                */
/*==============================================================*/
create index TEM_FK on VENDAS (
   COD_CLIENTE ASC
);

/*==============================================================*/
/* Index: INCLUI_FK                                             */
/*==============================================================*/
create index INCLUI_FK on VENDAS (
   COD_PRODUTO ASC
);

alter table ENTRADA
   add constraint FK_ENTRADA_CONTEM_PRODUTO foreign key (COD_PRODUTO)
      references PRODUTO (COD_PRODUTO);

alter table ENTRADA
   add constraint FK_ENTRADA_CONTROLAD_FUNCIONA foreign key (NOME_FUNCIONARIO)
      references FUNCIONARIO (NOME_FUNCIONARIO);

alter table ENTRADA
   add constraint FK_ENTRADA_FORNECIDA_FORNECED foreign key (COD_FORNECEDOR)
      references FORNECEDOR (COD_FORNECEDOR);

alter table GERIDA
   add constraint FK_GERIDA_GERIDA_SECCOES foreign key (COD_SECCAO)
      references SECCOES (COD_SECCAO);

alter table GERIDA
   add constraint FK_GERIDA_GERIDA2_FUNCIONA foreign key (NOME_FUNCIONARIO)
      references FUNCIONARIO (NOME_FUNCIONARIO);

alter table PRODUTO
   add constraint FK_PRODUTO_PERTENCEM_SECCOES foreign key (COD_SECCAO)
      references SECCOES (COD_SECCAO);

alter table VENDAS
   add constraint FK_VENDAS_INCLUI_PRODUTO foreign key (COD_PRODUTO)
      references PRODUTO (COD_PRODUTO);

alter table VENDAS
   add constraint FK_VENDAS_TEM_CLIENTE foreign key (COD_CLIENTE)
      references CLIENTE (COD_CLIENTE);

