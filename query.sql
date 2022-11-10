create table tipo_cliente (id_typecli serial primary key, tipo varchar not null);

create table clientes (id_cliente serial primary key,
 id_typecli int references tipo_cliente(id_typecli),
  nombre varchar not null, fecha_inicio date not null default now(), 
  deuda float not null default 0.0, credito float default 0.0);

create table ventas (id_venta serial primary key,
id_cliente int references clientes(id_cliente), 
tipo_pago varchar not null, total float not null, 
fecha date not null default now());

create table articulos (id_articulo serial primary key, 
nombre varchar not null, marca varchar default 'GENERICA', 
descripcion varchar, precio_uni float not null);

create table det_ventas (cns serial primary key, 
id_venta int references ventas(id_venta), 
id_articulo int references articulos(id_articulo),cantidad int not null default 0, 
descuento int not null default 0, subtotal_base float not null, 
subtotal_final float not null);

create table inventario (id_inventario serial primary key, 
id_articulo int references articulos(id_articulo), 
cantidad int not null default 0,nivel varchar default 'sin existencia', 
no_ventas int default 0);

create or replace function nivel (id integer) returns text as $$
declare
resultado text;
cantidad RECORD;

begin
    SELECT INTO cantidad * FROM inventario WHERE id_articulo=id;
	if cantidad < 7 then
	resultado:= 'inventario por agotar';
    update inventario set nivel='inventario por agotar';
    end if;
    if cantidad==0 then
	resultado:= 'inventario agotado';
    update inventario set nivel='inventario agotado';
    end if;
    if cantidad>6 then
	resultado:= 'inventario suficiente';
    update inventario set nivel='inventario suficiente';
    end if;   
return resultado;
end;
$$ language plpgsql;



create or replace function nivel (id integer) returns text as $$
declare
resultado text;
cantidad RECORD;

begin
    SELECT * INTO cantidad FROM inventario WHERE id_articulo=id;
	if cantidad.cantidad < 7 then
	resultado:= 'inventario por agotar';
    update inventario set nivel='inventario por agotar' WHERE inventario.id_inventario = id;
    end if;
    if cantidad.cantidad=0 then
	resultado:= 'inventario agotado';
    update inventario set nivel='inventario agotado' WHERE inventario.id_inventario = id;
    end if;
    if cantidad.cantidad>6 then
	resultado:= 'inventario suficiente';
    update inventario set nivel='inventario suficiente' WHERE inventario.id_inventario = id;
    end if;   
return resultado;
end;
$$ language plpgsql;


create or replace function f_descuento (id integer) returns text as $$
declare
resultado int;
mes RECORD;
fecha_inicio RECORD;

begin
    update clientes set fecha_descuento=(select EXTRACT(MONTH FROM clientes.fecha_inicio) from clientes WHERE clientes.id_cliente=id) WHERE clientes.id_cliente = id;
    return 'hecho';
end;
$$ language plpgsql;


create or replace function credito (id integer) returns text as $$
declare
resultado text;
type_cliente RECORD;

begin
    SELECT * INTO type_cliente FROM clientes WHERE id_cliente=id;
	if type_cliente.id_typecli >1 then
	resultado:= 'Con credito';
    update clientes set credito=10000.00 WHERE clientes.id_cliente = id;
    end if;
    if type_cliente.id_typecli <2 then
	resultado:= 'Sin credito';
    update clientes set credito=0.00 WHERE clientes.id_cliente = id;
    end if;
   
  
return resultado;
end;
$$ language plpgsql;