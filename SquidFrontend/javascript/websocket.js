/**
 * @author W.Sanquer
 */
// Ouvre une connexion directe avec le serveur.
const socket = new WebSocket("ws://localhost:1234");
// Attend la connexion et envoie le pseudo au serveur pour s'authentifier.
socket.onopen = () => {
    console.log("Connecte au serveur");
    socket.send(JSON.stringify({
        type: "auth/register",
        timestamp: new Date().toISOString(),
        payload: {
            pseudo: pseudo
        }
    }));
};
// Des que le serveur envoie un message il l'affiche dans la zone des messages.
socket.onmessage = (event) => {
    const reponse = JSON.parse(event.data);
    // Message du forum
    if (reponse.type === "forum/send") {
        const msg = document.createElement("p");
        msg.textContent = reponse.payload.from + " : " + reponse.payload.content;
        document.querySelector(".messages").appendChild(msg);
    }
    // Confirmation d'authentification
    if (reponse.type === "auth/ack") {
        if (reponse.payload.status === "error") {
            // Pseudo refusé → supprime la session et redirige vers index
            sessionStorage.removeItem("pseudo");
            window.location.href = "../index.html";
        } else {
            console.log("Authentifie :", reponse.payload.pseudo);
        }
    }
};
// Affiche dans le terminal JS quand la connexion avec le serveur est coupee
socket.onclose = () => {
    console.log("Connexion perdu");
};