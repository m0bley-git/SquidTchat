/*****************************************************
 * PROJECT : SquidTchat
 * AUTHOR  : W.Sanquer
 * DATE    : 2026
 *****************************************************/

/* ===================================================
    Regarde dans la memoire de la session si un pseudo est enregistre
   =================================================== */

const pseudo = sessionStorage.getItem("pseudo");

/* ===================================================
    Si aucun pseudo enregistrer dans la memoire redirection
   =================================================== */

if (!pseudo) {
    window.location.href = "/index.html";
}