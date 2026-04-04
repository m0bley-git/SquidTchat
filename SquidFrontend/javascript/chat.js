/*****************************************************
 * PROJECT : SquidTchat
 * AUTHOR  : W.Sanquer
 * DATE    : 2026
 *****************************************************/

/* ===================================================
    Preparation et expedition du message vers le serveur
   =================================================== */
function envoyerMessage() {
    const input = document.querySelector('.saisie');
    const texte = input.value.trim();
    
    // Si la zone de texte est vide, on arrête tout ici
    if (!texte) return;

    // Je transforme le texte en message en JSON pour le serveur
    socket.send(JSON.stringify({
        type: "forum/send",
        timestamp: new Date().toISOString(),
        payload: {
            pseudo: pseudo,
            content: texte
        }
    }));

    // Je vide la zone de texte pour le prochain message
    input.value = '';
}

/* ===================================================
    Raccourci clavier pour la touche entrer 
   =================================================== */
document.querySelector('.saisie').addEventListener('keydown', (e) => {
    if (e.key === 'Enter') envoyerMessage();
});