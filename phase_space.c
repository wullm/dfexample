/*******************************************************************************
 * Copyright (c) 2021 Willem Elbers (whe@willemelbers.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/

/* A custom header like this can be generated with the main program! */
#include "phase_space.h"

/* Standard headers */
#include <stdio.h>
#include <sys/time.h>

int main() {

    /* Total number of neutrino particles */
    long long nr_nuparts = 256 * 256 * 256;

    /* Comoving physical sidelength of the box */
    double box_length = 256; // Mpc

    /* Compute tha conversion factor from microscopic mass in electronvolts
     * to simulation particle mass in internal mass units */
    double mass_factor = neutrino_mass_factor(nr_nuparts, box_length);

    /* Prepare generating a particle */
    uint64_t id = 1000000; /* Particle id, used as random seed */
    double v[3];           /* Particle velocity */
    double x[3];           /* Particle position */
    double w;              /* Particle weight */
    double m_eV = 0.05;    /* Neutrino mass in electronvolts */

    printf("microscopic mass = %f eV\n", m_eV);
    printf("unweighted mass = %f 10^10 M_sol\n\n", m_eV / mass_factor);

    /* Initialize the particle with a random position and velocity */
    init_neutrino_particle(id, m_eV, v, x, &w, box_length);

    /* Print some information about the particle */
    printf("Particle initialized with:\n");
    printf("x[3] = (%.3f, %.3f, %.3f) Mpc\n", x[0], x[1], x[2]);
    printf("v[3] = (%.3f, %.3f, %.3f) Mpc/Gyr\n", v[0], v[1], v[2]);
    printf("weight = %e 10^10 M_sol\n\n", w);

    /* Update the velocity with a kick */
    v[0] *= 1.001;
    v[1] *= 0.999;
    v[2] *= 1.002;

    /* Update the particle weight */
    update_neutrino_particle(id, m_eV, v, x, &w, mass_factor);

    /* Print some information about the particle */
    printf("Particle state after update:\n");
    printf("x[3] = (%.3f, %.3f, %.3f) Mpc\n", x[0], x[1], x[2]);
    printf("v[3] = (%.3f, %.3f, %.3f) Mpc/Gyr\n", v[0], v[1], v[2]);
    printf("weight = %e 10^10 M_sol\n", w);

    return 0;
}
