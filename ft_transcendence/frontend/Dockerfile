# FROM node:lts # too big
FROM node:lts-alpine

LABEL maintainer="https://github.com/42-Tomodachi" 

RUN mkdir -p /app/Tomodachi/FE

WORKDIR /app/Tomodachi/FE

# COPY ./ /app/Tomodachi/FE

# RUN chmod +x ./ENTRYPOINT.sh

EXPOSE 3000

ENTRYPOINT ["./ENTRYPOINT.sh"]