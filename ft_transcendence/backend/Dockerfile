FROM node:16-alpine

WORKDIR /app
# COPY ./ /app/

RUN apk add --no-cache bash 
# RUN npm install
# RUN npm run build

EXPOSE 5500

ENTRYPOINT ["./wait-for-it.sh", "postgresql:5432", "--", "npm", "start"]
