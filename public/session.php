<?php
// Start the session
session_start();

// Generate a unique session ID if it doesn't exist
if (!isset($_SESSION['session_id'])) {
    $_SESSION['session_id'] = session_id();
}

// Output the session ID
echo $_SESSION['session_id'];
?>