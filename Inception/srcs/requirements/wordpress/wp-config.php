<?php
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the
 * installation. You don't have to use the web site, you can
 * copy this file to "wp-config.php" and fill in the values.
 *
 * This file contains the following configurations:
 *
 * * MySQL settings
 * * Secret keys
 * * Database table prefix
 * * ABSPATH
 *
 * @link https://wordpress.org/support/article/editing-wp-config-php/
 *
 * @package WordPress
 */

// ** MySQL settings - You can get this info from your web host ** //
/** The name of the database for WordPress */
define( 'DB_NAME', 'MYSQL_DATABASE' );

/** MySQL database username */
define( 'DB_USER', 'MYSQL_USER' );

/** MySQL database password */
define( 'DB_PASSWORD', 'MYSQL_PASSWORD' );

/** MySQL hostname */
define( 'DB_HOST', 'mariadb_service:3306' );

/** Database Charset to use in creating database tables. */
define( 'DB_CHARSET', 'utf8' );

/** The Database Collate type. Don't change this if in doubt. */
define( 'DB_COLLATE', '' );

define( 'WP_ALLOW_REPAIR', true );

/**#@+
 * Authentication Unique Keys and Salts.
 *
 * Change these to different unique phrases!
 * You can generate these using the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}
 * You can change these at any point in time to invalidate all existing cookies. This will force all users to have to log in again.
 *
 * @since 2.6.0
 */
define('AUTH_KEY',         'ssry9u^~U|6ezor!|^ME#&PK5<Y[Am[p~Pc+wI=H%C-F(S|Z,#_cFgR|tm*+Phf|');
define('SECURE_AUTH_KEY',  ',+g*mOx#@Llh:7v]+<|&-_aAR2q+5<s-#!7FT5V|zBPgu?fx|nB-c;#r;|Als)9+');
define('LOGGED_IN_KEY',    'hjC0cMUgFP|eVZN?S#1~=6|JwVB #CjZ?}G@kRE+F6OxQc[22DSyRwV$2xYcLYIJ');
define('NONCE_KEY',        ':dZJ-ED|/kD6h-D<vblEXqvfW7--JGZC_qla|rsv((+Of>ElhGVpGS.CU2APu;x.');
define('AUTH_SALT',        'xv(#FS!Bf{2QWP,Q/G5;tVmXa3b&~%3xQ*P-U/mq89L~X#sgQPtg~6C5a+m`>O-(');
define('SECURE_AUTH_SALT', 'D!(SSde.:dv*I*ll]%}5F?Ax>GwJ2& p|L%2Rtk+g(yq$Fy1(.iyoxR9]7!vc{QO');
define('LOGGED_IN_SALT',   'l|67>z6&{1nAbVMwX+q7CbHW%p5? D3 EAUC(cabcE2v#fgbn1RfJu|`|K|fS7>$');
define('NONCE_SALT',       '20!+]%rYh|_#CfWlW{[^N+Jxy`JpM!+]k.h[P(^p]cL07RC^<LGk@4F/.{sY&/<q');

/**#@-*/

/**
 * WordPress Database Table prefix.
 *
 * You can have multiple installations in one database if you give each
 * a unique prefix. Only numbers, letters, and underscores please!
 */
$table_prefix = 'wp_';

/**
 * For developers: WordPress debugging mode.
 *
 * Change this to true to enable the display of notices during development.
 * It is strongly recommended that plugin and theme developers use WP_DEBUG
 * in their development environments.
 *
 * For information on other constants that can be used for debugging,
 * visit the documentation.
 *
 * @link https://wordpress.org/support/article/debugging-in-wordpress/
 */
define( 'WP_DEBUG', true );

/* That's all, stop editing! Happy publishing. */

/** Absolute path to the WordPress directory. */
if ( ! defined( 'ABSPATH' ) ) {
	define( 'ABSPATH', __DIR__ . '/' );
}

/** Sets up WordPress vars and included files. */
require_once ABSPATH . 'wp-settings.php';
?>

