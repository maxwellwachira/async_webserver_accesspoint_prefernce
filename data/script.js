const apiBaseUrl = "https://api.proxyauto.co.ke/proxy";

const form = document.getElementById("vehicleData");

const formContainer = document.getElementsByClassName("form");

const selectElement = document.getElementById('vehicleYOM');
  const currentYear = new Date().getFullYear();
  const minYear = 2000;

  // Generate the options dynamically
  for (let year = currentYear; year >= minYear; year--) {
    const option = document.createElement('option');
    option.value = year;
    option.text = year;
    selectElement.appendChild(option);
  }

const onSubmit = async (event) => {
    event.preventDefault();
    console.log("submitting...");

    const firstName = document.getElementById("firstName").value;
    const lastName = document.getElementById("lastName").value;
    const userName = document.getElementById("userName").value;
    const email = document.getElementById("email").value;
    const phoneNumber = document.getElementById("phoneNumber").value;
    const whatsAppNumber = document.getElementById("whatsAppNumber").value;
    const registrationNumber = document.getElementById("registrationNumber").value;
    const vehicleMake = document.getElementById("vehicleMake").value;
    const vehicleModel = document.getElementById("vehicleModel").value;
    const vehicleYOM = document.getElementById("vehicleYOM").value;
    const chassisNumber = document.getElementById("chassisNumber").value;


    const vehicleEnrollData = {
        username: userName,
        email,
        telephone: phoneNumber,
        registrationNumber: "", //this is ID
        whatsappTelephone: whatsAppNumber,
        firstName,
        lastName,
        vehicleRegistrationNumber: registrationNumber,
        vehicleMake,
        model: vehicleModel,
        yearOfMake: vehicleYOM,
        vehicleTelephone: '',
        chasisNumber: chassisNumber,
        imei: ''
    };

    console.log(vehicleEnrollData);

    const options = {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(vehicleEnrollData)
    };

    try {
        const response = await fetch("/submit", options);
        const data = await response.text();

        if(data == "Data received successfully"){
            formContainer[0].innerHTML = `
            <div class="success">
                <p>ScanMax Device Data for ${registrationNumber} has been saved successfully</p>
            </div>  
            `;
        }else{
            formContainer[0].innerHTML = `
            <div class="error">
                <p>Error: ${data}
                    Refresh page to input data again
                </p>
            </div>  
            `;
        }
        console.log(data);
    } catch (error) {
        console.error(error);
    }
}

form.addEventListener('submit', onSubmit);