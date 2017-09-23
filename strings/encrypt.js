'use strict';

class Encrypt {
    constructor(props) {
        this.start = props.start.charCodeAt()
        this.final = props.final.charCodeAt()
    }

    code(str, rotation) {
        let alpha = (this.final - this.start) + 1
        let str_norm = str.charCodeAt() - this.start
        let rotation_norm = rotation % alpha

        let rotated = ((str_norm + rotation) % alpha) + this.start;

        return String.fromCharCode(rotated)
    }

}

function encrypt_phrase(str, rotation) {
    let e = new Encrypt({ start: 'a', final: 'z' })
    let E = new Encrypt({ start: 'A', final: 'Z' })

    str = str
        .split('')
        .map((chr) => {
            if (chr.search(/[A-Za-z]/) !== -1) {

                if (chr === chr.toUpperCase())
                    return E.code(chr, rotation)
                else
                    return e.code(chr, rotation)
            }

            return chr
        })
        .join('')

    return str
}

console.log('testing encrypting 159357lcfd ==>', encrypt_phrase('159357lcfd', 98) === '159357fwzx' ? 'passing' : 'failing')
console.log('testing encrypting middle-Outz ==>',encrypt_phrase('middle-Outz', 2) === 'okffng-Qwvb'?'passing':'failing')
console.log(encrypt_phrase(encrypt_phrase('middle-Outz', 2), -2))
