'use strict';


export function Strip_Leading_Zeroes(str) {
    let str2 = str.replace(/^0+/, '');
    if (str2 === '') {
        return '0';
    }
    return str2;
}