drop database if exists pinkfloyd;
create database pinkfloyd;
use pinkfloyd;

create table albums(
	idalbum int auto_increment,
    album_name varchar(256) not null,
    year int not null,
    primary key(idalbum)
);

create table songs(
	idsong int auto_increment not null, 
    song_name varchar(256),
    idalbum int not null,
    foreign key(idalbum) references albums(idalbum),
    primary key(idsong)
)


