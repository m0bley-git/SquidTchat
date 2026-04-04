# ============================================================
# PROJECT : SquidTchat
# AUTHOR  : W.Sanquer
# DATE    : 2026
# ============================================================

# Image de base Debian légère
FROM debian:bookworm-slim

# Installation de Qt6 et des outils de compilation
RUN apt-get update && apt-get install -y \
    qt6-base-dev \
    qt6-websockets-dev \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# Copie uniquement les sources du backend dans le conteneur
COPY SquidBackend/src/ /app/

# Se place dans le dossier de travail
WORKDIR /app

# Compile le projet (SquidBackend.pro est le bon nom du fichier)
RUN qmake6 SquidBackend.pro && make

# Expose le port WebSocket
EXPOSE 1234

# Lance le serveur au démarrage
CMD ["./SquidBackend"]